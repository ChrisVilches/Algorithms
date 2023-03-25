#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int N, M;
vector<vector<bool>> grid;
vector<pii> border_cells;

const pii LEFT{0, -1};
const pii RIGHT{0, 1};
const pii UP{1, 0};
const pii DOWN{-1, 0};

pii turn_left(const pii dir) { return {dir.second, -dir.first}; }
pii turn_right(const pii dir) { return {-dir.second, dir.first}; }

pii operator+(const pii a, const pii b) {
  return {a.first + b.first, a.second + b.second};
}

bool cell_ok(const pii cell) {
  const auto [i, j] = cell;
  return i >= 0 && j >= 0 && i < N && j < M && !grid[i][j];
}

bool draw_path(const pii source, const pii target) {
  if (!cell_ok(source)) return false;

  pii dir;

  if (N == 1)
    dir = source.second < target.second ? RIGHT : LEFT;
  else if (M == 1)
    dir = source.first < target.first ? UP : DOWN;
  else
    dir = source.first == 0 || source.second == 0 ? RIGHT : LEFT;

  vector<pii> path{source};

  pii curr_cell = source;

  for (int it = 0; curr_cell != target; it++) {
    if (it > N * M) return false;

    if (cell_ok(curr_cell + turn_right(dir))) {
      dir = turn_right(dir);
    } else if (!cell_ok(curr_cell + dir)) {
      dir = turn_left(dir);
    }

    if (!cell_ok(curr_cell + dir)) continue;

    curr_cell = curr_cell + dir;
    path.push_back(curr_cell);
  }

  for (const auto& [i, j] : path) {
    grid[i][j] = true;
  }

  return true;
}

void precompute_border_cell_indices() {
  border_cells.clear();

  for (int i = N - 1; i >= 0; i--) border_cells.emplace_back(i, 0);
  for (int i = 0; i < M; i++) border_cells.emplace_back(0, i);
  for (int i = 0; i < N; i++) border_cells.emplace_back(i, M - 1);
  for (int i = M - 1; i >= 0; i--) border_cells.emplace_back(N - 1, i);
}

pii find_cell(int n) {
  n %= 2 * (N + M);
  return border_cells[n];
}

int calculate_dist(const int s, const int t) {
  const auto target_cell = find_cell(t);

  set<pii> all;

  for (int i = s;; i++) {
    const pii cell = find_cell(i);
    all.emplace(cell);

    if (cell == target_cell) break;
  }

  return all.size();
}

bool solve() {
  int L;
  cin >> N >> M >> L;
  grid.assign(N, vector<bool>(M, false));

  precompute_border_cell_indices();

  vector<tuple<int, pii, pii>> dist_pairs;

  for (int i = 0; i < L; i++) {
    int s, t;
    cin >> s >> t;
    s--;
    t--;

    const pii s_cell = find_cell(s);
    const pii t_cell = find_cell(t);
    const int dist_s_t = calculate_dist(s, t);
    const int dist_t_s = calculate_dist(t, s);

    if (dist_s_t < dist_t_s) {
      dist_pairs.emplace_back(dist_s_t, s_cell, t_cell);
    } else {
      dist_pairs.emplace_back(dist_t_s, t_cell, s_cell);
    }
  }

  sort(dist_pairs.begin(), dist_pairs.end());

  for (const auto& [_, s, t] : dist_pairs)
    if (!draw_path(s, t)) return false;

  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  while (T--) {
    cout << (solve() ? "YES" : "NO") << endl;
  }
}
