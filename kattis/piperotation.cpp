#include <bits/stdc++.h>
using namespace std;
#define MAX_N 107

char grid[MAX_N][MAX_N];
int N, M, hor[MAX_N][MAX_N], ver[MAX_N][MAX_N];

void update(int matrix[][MAX_N], const int i, const int j, const int x) {
  if (i < 0 || j < 0) return;
  matrix[i][j] += x;
}

bool possible() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      const char c = grid[i][j];
      if (c == 'A') continue;

      const bool v = i > 0 && ver[i - 1][j];
      const bool h = j > 0 && hor[i][j - 1];

      switch (c) {
        case 'D':
          update(ver, i - 1, j, -1);
          update(hor, i, j - 1, -1);
          update(ver, i, j, 1);
          update(hor, i, j, 1);
          break;
        case 'B':
          if (h) {
            update(hor, i, j - 1, -1);
            update(hor, i, j, 1);
          } else {
            update(ver, i - 1, j, -1);
            update(ver, i, j, 1);
          }
          break;
        case 'C':
          if (v) {
            update(ver, i - 1, j, -1);
          } else {
            update(ver, i, j, 1);
          }

          if (h) {
            update(hor, i, j - 1, -1);
          } else {
            update(hor, i, j, 1);
          }
          break;
      }
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (ver[i][j] || hor[i][j]) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  while (cin >> N >> M) {
    memset(hor, 0, sizeof hor);
    memset(ver, 0, sizeof ver);

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        cin >> grid[i][j];
      }
    }

    cout << (possible() ? "Possible" : "Impossible") << endl;
  }
}
