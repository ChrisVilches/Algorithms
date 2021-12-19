#include <bits/stdc++.h>
using namespace std;

int M, N;
char grid[101][101];
int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};

void dfs(int i, int j) {
  if (grid[i][j] == '#') return;
  for (int d = 0; d < 4; d++) {
    int i2 = i + di[d];
    int j2 = j + dj[d];

    if (i2 < 0 || j2 < 0) continue;
    if (i2 >= M || j2 >= N) continue;
    grid[i][j] = '#';
    dfs(i2, j2);
  }
}

int main() {
  int test = 1;

  while (scanf("%d %d", &M, &N) == 2) {
    for (int i = 0; i < M; i++)
      for (int j = 0; j < N; j++) scanf(" %c", &grid[i][j]);

    int total = 0;

    for (int i = 0; i < M; i++)
      for (int j = 0; j < N; j++)
        if (grid[i][j] == '-') {
          total++;
          dfs(i, j);
        }

    printf("Case %d: %d\n", test++, total);
  }
}
