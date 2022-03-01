#include <bits/stdc++.h>
using namespace std;

#define MAX_SCORE 75

double memo[MAX_SCORE][MAX_SCORE][MAX_SCORE];

double p(int i, int j, int k);

double p_hold(int i, int j, int k) { return 1 - p(j, i + k, 0); }

double p_continue(int i, int j, int k) {
  double result = 1 - p(j, i, 0);
  for (int dice = 2; dice <= 6; dice++) result += p(i, j, k + dice);
  return result / 6;
}

double p_approximate(int i, int j) {
  double prob = 0.5;

  array<double, MAX_SCORE + 1> approx;

  for (int t = 0; t < 41; t++) {
    for (int k = MAX_SCORE; k >= 0; k--) {
      double hold = 0;
      double roll = 0;

      if (k > 0 && i + k <= MAX_SCORE) {
        hold = p_hold(i, j, k);
      }

      for (int dice = 1; dice <= 6; dice++) {
        if (dice == 1 || k + dice > MAX_SCORE) {
          roll += 1 - prob;
        } else {
          roll += approx[k + dice];
        }
      }

      approx[k] = max(hold, roll / 6);
    }

    prob = approx[0];
    swap(i, j);
  }

  return prob;
}

double p(int i, int j, int k) {
  if (j == MAX_SCORE) return 0;
  if (i + k > MAX_SCORE) return 1 - p(j, i, 0);
  if (memo[i][j][k] > -1) return memo[i][j][k];

  double probability;

  if (k == 0)
    probability = p_approximate(i, j);
  else
    probability = max(p_hold(i, j, k), p_continue(i, j, k));

  return memo[i][j][k] = probability;
}

int main() {
  memset(memo, -1, sizeof memo);

  int Q;
  while (scanf("%d", &Q) == 1)
    while (Q--) {
      int C, H, X;
      cin >> C >> H >> X;

      double h = p_hold(C, H, X);
      double c = p_continue(C, H, X);
      cout << (h > c ? 'H' : 'C') << endl;
    }
}
