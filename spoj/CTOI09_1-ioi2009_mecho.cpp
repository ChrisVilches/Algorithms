#include <bits/stdc++.h>

using namespace std;
#define MAX 803
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

char original_grid[MAX][MAX];
char grid[MAX][MAX];
int bee_times[MAX][MAX];
int N, S;
int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};

inline bool valid_grid(int i, int j) {
  return !(i < 0 || j < 0 || i >= N || j >= N);
}

inline bool bear_walkable(int i, int j) {
  return valid_grid(i, j) && (grid[i][j] == 'G' || grid[i][j] == 'D');
}

inline bool valid_bee_grid(int i, int j) {
  return valid_grid(i, j) && grid[i][j] == 'G';
}

inline void visit(int i, int j) { grid[i][j] = 'T'; }

void grid_cpy() {
  for (int i = 0; i < N; i++)
    memcpy(grid[i], original_grid[i], sizeof(char) * N);
}

void calculate_bee_times() {
  grid_cpy();
  queue<tiii> q;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (grid[i][j] == 'H') q.push(make_tuple(i, j, 0));

  while (!q.empty()) {
    auto [i, j, t] = q.front();
    q.pop();
    bee_times[i][j] = t;
    for (int d = 0; d < 4; d++) {
      int i2 = i + di[d];
      int j2 = j + dj[d];
      if (!valid_bee_grid(i2, j2)) continue;
      visit(i2, j2);
      q.push(make_tuple(i2, j2, t + S));
    }
  }
}

bool possible(int minutes, pii from, pii to) {
  grid_cpy();
  queue<tiii> q;
  q.push(make_tuple(from.first, from.second, minutes));

  while (!q.empty()) {
    auto [i, j, t] = q.front();
    q.pop();
    if (to == make_pair(i, j)) return true;

    visit(i, j);

    if (bee_times[i][j] <= t) continue;

    for (int d = 0; d < 4; d++) {
      int i2 = i + di[d];
      int j2 = j + dj[d];
      if (!bear_walkable(i2, j2)) continue;
      visit(i2, j2);
      q.push(make_tuple(i2, j2, t + 1));
    }
  }
  return false;
}

void solve() {
  scanf("%d %d", &N, &S);
  pii mecho, home;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      scanf(" %c", &original_grid[i][j]);
      if (original_grid[i][j] == 'D')
        home = make_pair(i, j);
      else if (original_grid[i][j] == 'M') {
        mecho = make_pair(i, j);
        original_grid[i][j] = 'G';
      }
    }

  calculate_bee_times();

  int left = 0;
  int right = (N * N * N);
  int possible_time = -1;
  while (left < right) {
    int mid = (left + right) / 2;
    if (possible(mid, mecho, home)) {
      left = mid + 1;
      possible_time = mid;
    } else {
      right = mid;
    }
  }

  printf("%d\n", possible_time == -1 ? -1 : possible_time / S);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) solve();
}
