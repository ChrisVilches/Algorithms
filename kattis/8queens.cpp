#include <bits/stdc++.h>

using namespace std;

char grid[8][8];

bool queen_valid(int i, int j) {
  for (int x = 0; x < 8; x++) {
    if (x == j) continue;
    if (grid[i][x] == '*') return false;
  }

  for (int x = 0; x < 8; x++) {
    if (x == i) continue;
    if (grid[x][j] == '*') return false;
  }

  int n = i - 8;
  int m = j - 8;
  int iters = 19;

  while (iters--) {
    if (n == i && m == j) continue;
    if (n >= 0 && n < 8 && m >= 0 && m < 8)
      if (grid[n][m] == '*') return false;
    n++;
    m++;
  }

  n = i - 8;
  m = j + 8;
  iters = 19;

  while (iters--) {
    if (n == i && m == j) continue;
    if (n >= 0 && n < 8 && m >= 0 && m < 8)
      if (grid[n][m] == '*') return false;
    n++;
    m--;
  }

  return true;
}

bool valid() {
  int queen_count = 0;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      if (grid[i][j] == '*') {
        queen_count++;
        if (!queen_valid(i, j)) return false;
      }

  return queen_count == 8;
}

int main() {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) scanf("%c ", &grid[i][j]);

  cout << (valid() ? "valid" : "invalid") << endl;
}
