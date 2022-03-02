#include <bits/stdc++.h>
using namespace std;

double memo[76][76][76][38];

double p(int i, int j, int k, int t);

double p_hold(int i, int j, int k, int t) { return 1 - p(j, i + k, 0, t - 1); }

double p_continue(int i, int j, int k, int t) {
  double ret = 0;

  for (int dice = 1; dice <= 6; dice++) {
    if (dice == 1 || i + k + dice > 75)
      ret += 1 - p(j, i, 0, t - 1);
    else
      ret += p(i, j, k + dice, t);
  }
  return ret / 6;
}

double p(int i, int j, int k, int t) {
  if (t == 0) return 0.5;
  if (j == 75) return 0;
  if (i + k > 75) return 1 - p(j, i, 0, t);
  if (memo[i][j][k][t] > -1) return memo[i][j][k][t];

  return memo[i][j][k][t] = max(p_hold(i, j, k, t), p_continue(i, j, k, t));
}

int main() {
  memset(memo, -1, sizeof memo);
  int q, C, H, X;

  while (scanf("%d", &q) == 1) {
    while (q--) {
      scanf("%d %d %d", &C, &H, &X);
      double h = p_hold(C, H, X, 35);
      double c = p_continue(C, H, X, 35);

      printf("%c\n", h > c ? 'H' : 'C');
    }
  }
}
