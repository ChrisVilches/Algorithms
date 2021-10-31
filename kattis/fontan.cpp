#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

int R, C;

char grid[51][51];

int dj[] = {-1, 1};

void bfs() {
  queue<pii> q;
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++)
      if (grid[i][j] == 'V') q.push(make_pair(i, j));

  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();

    if (i == R - 1) continue;
    char& below = grid[i + 1][j];
    if (below == 'V') continue;

    if (below == '.') {
      below = 'V';
      q.push(make_pair(i + 1, j));
    } else {
      for (int d = 0; d < 2; d++) {
        int j2 = j + dj[d];
        if (j2 < 0 || j2 == C) continue;
        char& side = grid[i][j2];
        if (side == '.') {
          side = 'V';
          q.push(make_pair(i, j2));
        }
      }
    }
  }
}

void solve() {
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++) scanf(" %c", &grid[i][j]);

  bfs();

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) cout << grid[i][j];
    cout << endl;
  }
}

int main() {
  while (scanf("%d %d", &R, &C) == 2) solve();
}
