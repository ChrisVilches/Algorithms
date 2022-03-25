#include <bits/stdc++.h>
using namespace std;
#define MAX 51

int N, M;
char grid[MAX][MAX];

bool visited[MAX * MAX];
int match[MAX * MAX];

const int di[] = {-1, 1, 0, 0};
const int dj[] = {0, 0, -1, 1};

bool bpm(const vector<vector<int>>& g, const int u) {
  for (int v : g[u])
    if (!visited[v]) {
      visited[v] = true;
      if (match[v] < 0 || bpm(g, match[v])) {
        match[v] = u;
        return true;
      }
    }
  return false;
}

int max_bipartite_matching(const vector<vector<int>>& g) {
  memset(match, -1, sizeof match);
  int result = 0;
  for (int u = 0; u < (int)g.size(); u++) {
    memset(visited, 0, sizeof visited);
    result += bpm(g, u);
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N >> M) {
    int free_tiles = 0;

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        cin >> grid[i][j];

        free_tiles += grid[i][j] == '.';
      }
    }

    vector<vector<int>> graph(N * M);

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (grid[i][j] == 'X') continue;

        for (int d = 0; d < 4; d++) {
          const int i2 = i + di[d];
          const int j2 = j + dj[d];

          if (i2 < 0 || j2 < 0 || i2 >= N || j2 >= M) continue;
          if (grid[i2][j2] == 'X') continue;

          const int u = (M * i) + j;
          const int v = (M * i2) + j2;

          graph.at(u).push_back(v);
        }
      }
    }

    cout << (max_bipartite_matching(graph) == free_tiles ? 2 : 1) << endl;
  }
}
