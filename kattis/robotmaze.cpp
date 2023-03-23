#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef tuple<pii, int, int, int, int> state;

bool visited[1003][1003][3][6][6];
int N, M;
char maze[1003][1003];
const int di[] = {0, -1, 1, 0, 0};
const int dj[] = {0, 0, 0, -1, 1};

bool is_opposite_dir(const int dir_idx1, const int dir_idx2) {
  if (dir_idx1 == 0 || dir_idx2 == 0) return false;
  if (dir_idx1 == dir_idx2) return false;

  return abs(di[dir_idx1]) == abs(di[dir_idx2]) || abs(dj[dir_idx1]) == abs(dj[dir_idx2]);
}

int solve() {
  cin >> N >> M;

  pii source, target;

  for (int i = 0; i < N; i++) {
    cin >> maze[i];

    for (int j = 0; j < M; j++) {
      if (maze[i][j] == 'R') source = {i, j};
      if (maze[i][j] == 'D') target = {i, j};
    }
  }

  memset(visited, 0, sizeof visited);
  queue<state> q;
  q.emplace(source, 2, 0, 0, 0);

  while (!q.empty()) {
    const auto [pos, remaining, curr_dir, prev_dir, dist] = q.front();
    q.pop();
    if (pos == target) return dist;

    // TODO: I had to add the visited checks here (otherwise MLE). Why?
    if (visited[pos.first][pos.second][remaining][curr_dir][prev_dir]) continue;
    visited[pos.first][pos.second][remaining][curr_dir][prev_dir] = true;

    for (int d = 1; d < 5; d++) {
      const int i2 = pos.first + di[d];
      const int j2 = pos.second + dj[d];

      if (i2 < 0 || j2 < 0 || i2 >= N || j2 >= M) continue;

      const int new_remaining = d == curr_dir ? remaining - 1 : 2;

      if (new_remaining == 0) continue;
      if (is_opposite_dir(prev_dir, d)) continue;
      if (maze[i2][j2] == 'B') continue;
      if (visited[i2][j2][new_remaining][d][d]) continue;

      q.emplace(make_pair(i2, j2), new_remaining, d, d, dist + 1);
    }
  }

  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  while (T--) cout << solve() << endl;
}
