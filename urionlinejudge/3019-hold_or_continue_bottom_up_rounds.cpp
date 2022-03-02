#include <bits/stdc++.h>
using namespace std;

double solution[76][76][76];

double p_hold(int i, int j, int k) { return 1 - solution[j][i + k][0]; }

double p_continue(int i, int j, int k) {
  double ret = 0;

  for (int dice = 1; dice <= 6; dice++) {
    if (dice == 1 || i + k + dice > 75)
      ret += 1 - solution[j][i][0];
    else
      ret += solution[i][j][k + dice];
  }
  return ret / 6;
}

int main() {
  int q, C, H, X, iter = 35;

  while (iter--) {
    for (int i = 0; i < 75; i++) {
      for (int j = 0; j < 75; j++) {
        for (int k = 75; k >= 0; k--) {
          solution[i][j][k] = max(p_hold(i, j, k), p_continue(i, j, k));
        }
      }
    }
  }

  while (scanf("%d", &q) == 1) {
    while (q--) {
      scanf("%d %d %d", &C, &H, &X);
      double h = p_hold(C, H, X);
      double c = p_continue(C, H, X);

      printf("%c\n", h > c ? 'H' : 'C');
    }
  }
}
