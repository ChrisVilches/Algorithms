#include <bits/stdc++.h>
using namespace std;

char grid[1001][1001];

int N, M;
int di[] = {1, -1, 0, 0};
int dj[] = {0, 0, 1, -1};
bool possible;

void dfs(const int i, const int j) {
  if (grid[i][j] == '1') return;

  if (i == N - 1) {
    possible = true;
  }

  grid[i][j] = '1';

  for (int d = 0; d < 4; d++) {
    int i2 = i + di[d];
    int j2 = j + dj[d];

    if (i2 >= 0 && j2 >= 0 && i2 < N && j2 < M && grid[i2][j2] == '0') {
      dfs(i2, j2);
    }
  }
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) {
    possible = false;

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        scanf(" %c", &grid[i][j]);
      }
    }

    for (int i = 0; i < M; i++) {
      dfs(0, i);
    }

    cout << (possible ? "YES" : "NO") << endl;
  }
}
