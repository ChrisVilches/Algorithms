#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

#define GOAL_SCORE 75

ld solve_memo[GOAL_SCORE][GOAL_SCORE];
ld p_memo[GOAL_SCORE][GOAL_SCORE][GOAL_SCORE];

ld solve(int A, int B) {
  if (solve_memo[A][B] > -1) return solve_memo[A][B];
  ld p = 0.5L;

  array<ld, GOAL_SCORE + 1> a;

  for (int t = 0; t < 100; t++) {
    swap(A, B);

    for (int i = 0; i <= GOAL_SCORE; i++) {
      if (i == 0 || A + i > GOAL_SCORE) {
        a[i] = 1 - p;
      } else if (A + i == GOAL_SCORE) {
        a[i] = 1;
      } else {
        a[i] = 1 - solve(B, A + i);
      }
    }

    for (int i = GOAL_SCORE - A - 1; i >= 0; i--) {
      ld curr = 1 - p;
      for (int j = 2; j <= 6; j++) {
        if (i + j <= GOAL_SCORE) {
          curr += a[i + j];
        } else {
          curr += 1 - p;
        }
      }
      a[i] = max(a[i], curr / 6);
    }
    p = a[0];
  }

  return solve_memo[A][B] = p;
}

ld p(int i, int j, int k);

ld p_hold(int i, int j, int k) { return 1 - p(j, i + k, 0); }

ld p_continue(int i, int j, int k) {
  ld result = 1 - p(j, i, 0);
  for (int dice = 2; dice <= 6; dice++) result += p(i, j, k + dice);
  return result / 6;
}

ld p(int i, int j, int k) {
  if (j == 75) return 0;
  if (i + k > 75) return 1 - p(j, i, 0);
  if (k == 0) return solve(i, j);

  if (p_memo[i][j][k] > -1) return p_memo[i][j][k];

  return p_memo[i][j][k] = max(p_hold(i, j, k), p_continue(i, j, k));
}

int main() {
  memset(p_memo, -1, sizeof p_memo);
  memset(solve_memo, -1, sizeof solve_memo);

  int q;
  while (scanf("%d", &q) == 1)
    while (q--) {
      int A, B, X;
      cin >> A >> B >> X;

      ld ph = p_hold(A, B, X);
      ld pc = p_continue(A, B, X);

      if (ph > pc) {
        cout << 'H' << endl;
      } else {
        cout << 'C' << endl;
      }
    }
}
