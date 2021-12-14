#include <bits/stdc++.h>
using namespace std;

int N, M;
char grid[101][101];
int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};

bool shop_adjacent_to_cell(int i, int j) {
  for (int d = 0; d < 4; d++) {
    int i2 = i + di[d];
    int j2 = j + dj[d];

    if (i2 < 0 || i2 >= N) continue;
    if (j2 < 0 || j2 >= M) continue;

    if (grid[i2][j2] == 'E') return true;
  }

  return false;
}

bool should_put_shop(int i, int j) {
  return grid[i][j] != '#' && !shop_adjacent_to_cell(i, j);
}

void solve() {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++) {
      scanf(" %c", &grid[i][j]);
    }

  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      if (should_put_shop(i, j)) {
        grid[i][j] = 'E';
      }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      printf("%c", grid[i][j]);
    }
    putchar('\n');
  }
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) solve();
}
