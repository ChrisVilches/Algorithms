#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

int N, M;
char grid[51][51];

int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};

void bfs(pii pos) {
  queue<pii> q;
  q.push(pos);

  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();
    grid[i][j] = '-';

    for (int d = 0; d < 4; d++) {
      int i2 = i + di[d];
      int j2 = j + dj[d];

      if (i2 < 0 || i2 >= N || j2 < 0 || j2 >= M) continue;
      if (grid[i2][j2] == 'W' || grid[i2][j2] == '-') continue;

      grid[i2][j2] = '-';
      q.push(make_pair(i2, j2));
    }
  }
}

void solve() {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++) scanf(" %c", &grid[i][j]);

  int ans = 0;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      if (grid[i][j] == 'L') {
        bfs(make_pair(i, j));
        ans++;
      }

  cout << ans << endl;
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) solve();
}
