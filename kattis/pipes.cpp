#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int N, M;
vector<vector<bool>> grid;
vector<vector<bool>> visited;
vector<pii> border_cells;

const pii LEFT{0, -1};
const pii RIGHT{0, 1};
const pii UP{1, 0};
const pii DOWN{-1, 0};

pii turn_left(const pii dir) { return {dir.second, -dir.first}; }
pii turn_right(const pii dir) { return {-dir.second, dir.first}; }

bool inside(const pii cell) {
  const auto [i, j] = cell;
  return i >= 0 && j >= 0 && i < N && j < M;
}

pii move(const pii cell, const pii dir) {
  return {cell.first + dir.first, cell.second + dir.second};
}

bool cell_ok(const pii cell) {
  if (!inside(cell)) return false;
  const auto [i, j] = cell;
  return !grid[i][j];
}

bool dfs(const pii cell, const pii target) {
  if (!cell_ok(cell)) return false;
  if (cell == target) return true;
  const auto [i, j] = cell;
  if (visited[i][j]) return false;
  visited[i][j] = true;

  return dfs(move(cell, LEFT), target) || dfs(move(cell, RIGHT), target) ||
         dfs(move(cell, UP), target) || dfs(move(cell, DOWN), target);
}

bool draw_path(const pii source, const pii target) {
  visited.assign(N, vector<bool>(M, false));
  if (!dfs(source, target)) return false;

  pii dir;

  if (N == 1)
    dir = source.second < target.second ? RIGHT : LEFT;
  else if (M == 1)
    dir = source.first < target.first ? UP : DOWN;
  else
    dir = source.first == 0 || source.second == 0 ? RIGHT : LEFT;

  vector<pii> path{source};

  pii curr_cell = source;

  while (curr_cell != target) {
    curr_cell = path.back();

    if (cell_ok(move(curr_cell, turn_right(dir)))) {
      dir = turn_right(dir);
    } else if (!cell_ok(move(curr_cell, dir))) {
      dir = turn_left(dir);
    }

    if (!cell_ok(move(curr_cell, dir))) {
      continue;
    }

    curr_cell = move(curr_cell, dir);
    path.push_back(curr_cell);
  }

  for (const auto& [i, j] : path) {
    grid[i][j] = true;
  }

  return true;
}

void precompute_border_cell_indices() {
  border_cells.clear();

  for (int i = 0; i < N; i++) border_cells.emplace_back(i, 0);
  for (int i = 0; i < M; i++) border_cells.emplace_back(N - 1, i);
  for (int i = N - 1; i >= 0; i--) border_cells.emplace_back(i, M - 1);
  for (int i = M - 1; i >= 0; i--) border_cells.emplace_back(0, i);
}

pii find_cell(int n) {
  n %= 2 * (N + M);
  return border_cells[n];
}

bool possible(const vector<pair<pii, pii>>& pairs) {
  grid.assign(N, vector<bool>(M, false));

  for (const auto& [s, t] : pairs) {
    // TODO: Why does this have to be t, s (swapped order) for it to work?
    if (!draw_path(t, s)) return false;
  }

  return true;
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

  vector<pii> st;

  map<int, pii> index_st_pair_map;

  for (int i = 0; i < L; i++) {
    int s, t;
    cin >> s >> t;
    s--;
    t--;
    st.emplace_back(s, i);
    st.emplace_back(t, i);

    index_st_pair_map[i] = {s, t};
  }

  precompute_border_cell_indices();

  vector<tuple<int, pii, pii>> dist_pairs;

  for (const auto& [idx, st_pair] : index_st_pair_map) {
    const auto [s, t] = st_pair;

    const auto s_cell = find_cell(s);
    const auto t_cell = find_cell(t);
    const int dist_s_t = calculate_dist(s, t);
    const int dist_t_s = calculate_dist(t, s);

    if (dist_s_t < dist_t_s) {
      dist_pairs.emplace_back(dist_s_t, s_cell, t_cell);
    } else {
      dist_pairs.emplace_back(dist_t_s, t_cell, s_cell);
    }
  }

  sort(dist_pairs.begin(), dist_pairs.end());

  vector<pair<pii, pii>> pairs;
  for (const auto& [_, s, t] : dist_pairs) pairs.emplace_back(s, t);

  return possible(pairs);
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
