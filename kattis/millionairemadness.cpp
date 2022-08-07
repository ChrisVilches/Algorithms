#include <bits/stdc++.h>
using namespace std;

int matrix[1001][1001];
const int di[] = {-1, 1, 0, 0};
const int dj[] = {0, 0, -1, 1};

int main() {
  int N, M;

  while (cin >> M >> N) {
    for (int i = 0; i < M; i++)
      for (int j = 0; j < N; j++) cin >> matrix[i][j];

    vector<vector<int>> dist(M, vector<int>(N, INT_MAX));

    priority_queue<tuple<int, int, int>> q;

    q.emplace(0, 0, 0);
    dist[0][0] = 0;

    while (!q.empty()) {
      const auto [_, i, j] = q.top();
      q.pop();

      for (int d = 0; d < 4; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];

        if (i2 < 0 || j2 < 0 || i2 >= M || j2 >= N) continue;

        const int height = max(0, matrix[i2][j2] - matrix[i][j]);
        const int alt = max(dist[i][j], height);

        if (alt < dist[i2][j2]) {
          dist[i2][j2] = alt;
          q.emplace(-alt, i2, j2);
        }
      }
    }

    cout << dist.back().back() << endl;
  }
}
