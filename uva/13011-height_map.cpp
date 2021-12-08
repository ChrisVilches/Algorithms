#include <bits/stdc++.h>

using namespace std;
#define MAX 101

int dj[4] = {0, 0, 1, -1};
int di[4] = {1, -1, 0, 0};

int R, C;
int mat1[MAX][MAX];
int mat2[MAX][MAX];
int mat3[MAX][MAX];
int mat4[MAX][MAX];

bool continuous(int a, int b, int c, int d) {
  if (a < c && c < b && b < d) return true;
  if (c < a && a < d && d < b) return true;
  if (c < a && a < b && b < d) return true;
  if (a < c && c < d && d < b) return true;
  if (a >= d || b <= c) return false;
  return true;
}

int north_faces(int (&m)[MAX][MAX], int r, int c) {
  int total = 0;
  for (int i = 0; i < r - 1; i++) {
    bool face = false;
    int prev_top = 0;
    int prev_bottom = 0;
    for (int j = 0; j < c; j++) {
      int bottom = m[i][j];
      int top = m[i + 1][j];
      switch (face) {
        case true:
          if (continuous(prev_bottom, prev_top, bottom, top)) break;
          if (bottom < top)
            total++;
          else
            face = false;
          break;
        case false:
          if (bottom < top) {
            face = true;
            total++;
          }
          break;
      }
      prev_top = top;
      prev_bottom = bottom;
    }
  }
  return total;
}

void dfs(int i, int j) {
  int val = mat1[i][j];
  mat1[i][j] = -1;
  for (int d = 0; d < 4; d++) {
    int new_i = i + di[d];
    int new_j = j + dj[d];
    if (new_j >= 0 && new_j < C && new_i >= 0 && new_i < R &&
        mat1[new_i][new_j] == val)
      dfs(new_i, new_j);
  }
}

void solve() {
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++) {
      int val;
      cin >> val;
      mat1[i][j] = val;
      mat2[j][R - 1 - i] = val;
      mat3[R - 1 - i][C - 1 - j] = val;
      mat4[C - 1 - j][i] = val;
    }

  int top_faces = 0;
  int side_faces = north_faces(mat1, R, C) + north_faces(mat2, C, R) +
                   north_faces(mat3, R, C) + north_faces(mat4, C, R);

  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++)
      if (~mat1[i][j]) {
        dfs(i, j);
        top_faces++;
      }

  cout << 5 + top_faces + side_faces << endl;
}

int main() {
  while (scanf("%d %d", &R, &C) == 2) solve();
}
