#include <bits/stdc++.h>
using namespace std;

#define MAX_SCORE 75

double solve_memo[MAX_SCORE][MAX_SCORE];
double p_memo[MAX_SCORE][MAX_SCORE][MAX_SCORE];

double solve(int A, int B) {
  if (solve_memo[A][B] > -1) return solve_memo[A][B];
  double p = 0.5;

  array<double, MAX_SCORE + 1> a;

  for (int t = 0; t < 40; t++) {
    swap(A, B);

    for (int i = 0; i <= MAX_SCORE; i++) {
      if (i == 0 || A + i > MAX_SCORE) {
        a[i] = 1 - p;
      } else if (A + i == MAX_SCORE) {
        a[i] = 1;
      } else {
        a[i] = 1 - solve(B, A + i);
      }
    }

    for (int i = MAX_SCORE - A - 1; i >= 0; i--) {
      double curr = 1 - p;
      for (int dice = 2; dice <= 6; dice++) {
        if (i + dice <= MAX_SCORE) {
          curr += a[i + dice];
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

double p(int i, int j, int k);

double p_hold(int i, int j, int k) { return 1 - p(j, i + k, 0); }

double p_continue(int i, int j, int k) {
  double result = 1 - p(j, i, 0);
  for (int dice = 2; dice <= 6; dice++) result += p(i, j, k + dice);
  return result / 6;
}

double p(int i, int j, int k) {
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
      int C, H, X;
      cin >> C >> H >> X;

      double h = p_hold(C, H, X);
      double c = p_continue(C, H, X);
      cout << (h > c ? 'H' : 'C') << endl;
    }
}
