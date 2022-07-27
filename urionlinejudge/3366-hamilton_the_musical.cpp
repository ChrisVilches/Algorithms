#include <bits/stdc++.h>
using namespace std;

int N, graph[507][507];

long long hungarian_assignment(vector<vector<int>>& matrix) {
  const int n = matrix.size(), m = matrix.back().size();

  vector<int> u(n + 1), p(m + 1), way(m + 1);
  vector<long long> v(m + 1);

  for (int i = 1; i <= n; ++i) {
    p[0] = i;
    int j0 = 0;
    vector<int> minv(m + 1, INT_MAX);
    vector<bool> used(m + 1);

    do {
      used[j0] = true;
      const int i0 = p[j0];
      int j1 = 0;
      int delta = INT_MAX;
      for (int j = 1; j <= m; ++j)
        if (!used[j]) {
          const int cur = matrix[i0 - 1][j - 1] - u[i0] - v[j];
          if (cur < minv[j]) minv[j] = cur, way[j] = j0;
          if (minv[j] < delta) delta = minv[j], j1 = j;
        }
      for (int j = 0; j <= m; ++j)
        if (used[j])
          u[p[j]] += delta, v[j] -= delta;
        else
          minv[j] -= delta;
      j0 = j1;
    } while (p[j0] != 0);
    do {
      const int j1 = way[j0];
      p[j0] = p[j1], j0 = j1;
    } while (j0 != 0);
  }

  return -v[0];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N) {
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) cin >> graph[i][j];

    vector<vector<int>> matrix;

    for (int i = 0; i < N; i += 2) {
      matrix.push_back(vector<int>());

      for (int j = 0; j < N; j += 2) {
        int cost = 0;

        if (j > 0) cost += graph[i][j - 1];
        if (j < N - 1) cost += graph[i][j + 1];

        matrix.back().push_back(cost);
      }
    }

    cout << hungarian_assignment(matrix) << endl;
  }
}
