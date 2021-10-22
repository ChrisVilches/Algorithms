#include <bits/stdc++.h>

using namespace std;
typedef tuple<int, int, int> tiii;

#define MAX 185
int mat[MAX][MAX], N, M;

int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, 1, -1};

int read_binary() {
  char c;
  while (scanf("%c", &c) == 1 && !(c == '1' || c == '0'))
    ;
  return c == '1';
}

void multisource_bfs(int (&dist)[MAX][MAX]) {
  queue<tiii> q;
  bool visited[MAX][MAX];

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      visited[i][j] = false;
      dist[i][j] = 0;
      if (mat[i][j] == 1) q.push(make_tuple(i, j, 0));
    }
  }

  while (!q.empty()) {
    auto [i, j, accum] = q.front();
    q.pop();

    visited[i][j] = true;
    if (mat[i][j] == 0) dist[i][j] = accum;

    for (int d = 0; d < 4; d++) {
      int i2 = i + di[d];
      int j2 = j + dj[d];
      if (i2 >= 0 && j2 >= 0 && i2 < N && j2 < M && !visited[i2][j2]) {
        q.push(make_tuple(i2, j2, accum + 1));
        visited[i2][j2] = true;
      }
    }
  }
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++) mat[i][j] = read_binary();

  int dist[MAX][MAX];
  multisource_bfs(dist);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) cout << dist[i][j] << ' ';
    cout << endl;
  }
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
