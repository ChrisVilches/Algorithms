#include <bits/stdc++.h>
using namespace std;

int N;
double D, X[101], Y[101];

double dist(int i, int j) {
  return sqrt(pow(X[i] - X[j], 2) + pow(Y[i] - Y[j], 2));
}

void solve() {
  for (int i = 0; i < N; i++) scanf("%lf %lf", &X[i], &Y[i]);

  int sweet = 0;
  int sour = 0;

  for (int i = 0; i < N; i++) {
    bool fight = false;

    for (int j = 0; j < N; j++)
      if (i != j && dist(i, j) <= D) {
        fight = true;
        break;
      }

    sour += fight;
    sweet += !fight;
  }

  printf("%d sour, %d sweet\n", sour, sweet);
}

int main() {
  while (scanf("%lf %d", &D, &N) == 2 && N > 0) solve();
}
