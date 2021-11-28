#include <bits/stdc++.h>
using namespace std;

#define MAX_SCORE 75

double memo[MAX_SCORE][MAX_SCORE][MAX_SCORE];

double p_approximate(int A, int B) {
  if (memo[A][B][0] > -1) return memo[A][B][0];

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
        a[i] = 1 - p_approximate(B, A + i);
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

  return memo[A][B][0] = p;
}

double p(int i, int j, int k);

double p_hold(int i, int j, int k) { return 1 - p(j, i + k, 0); }

double p_continue(int i, int j, int k) {
  double result = 1 - p(j, i, 0);
  for (int dice = 2; dice <= 6; dice++) result += p(i, j, k + dice);
  return result / 6;
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
