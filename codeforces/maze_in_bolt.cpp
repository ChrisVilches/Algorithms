#include <bits/stdc++.h>
using namespace std;

int R, C;
array<string, 1001> maze;
const int di[] = {-1, 1, 0, 0};
const int dj[] = {0, 0, -1, 1};
bool visited[1001][101];

bool state_ok(const string& nut, const int i, int j) {
  for (const char c : nut) {
    if (c == '1' && maze[i][j % C] == '1') {
      return false;
    }
    j++;
  }

  return true;
}

bool bfs(const string& nut) {
  memset(visited, 0, sizeof visited);

  queue<pair<int, int>> q;
  for (int j = 0; j < C; j++) q.emplace(-1, j);

  while (!q.empty()) {
    const auto [i, j] = q.front();
    q.pop();

    if (i == R - 1) return true;

    for (int d = 0; d < 4; d++) {
      const int i2 = i + di[d];
      const int j2 = (j + dj[d] + C) % C;
      if (i2 < 0) continue;
      if (visited[i2][j2] || !state_ok(nut, i2, j2)) continue;

      visited[i2][j2] = true;
      q.emplace(i2, j2);
    }
  }

  return false;
}

bool possible(string nut) {
  if (bfs(nut)) return true;
  reverse(nut.begin(), nut.end());
  return bfs(nut);
}

int main() {
  while (cin >> R >> C) {
    string nut;
    cin >> nut;
    for (int i = 0; i < R; i++) cin >> maze[i];

    cout << (possible(nut) ? "Y" : "N") << endl;
  }
}
