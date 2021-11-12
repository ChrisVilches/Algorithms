#include <bits/stdc++.h>
using namespace std;

double L, W;

inline double volume(double x) { return (W - (2 * x)) * (L - (2 * x)) * x; }

int main() {
  while (scanf("%lf %lf", &L, &W) == 2) {
    double left = 0;
    double right = min(L, W) / 2.0;
    int iters = 100;

    while (iters--) {
      double third = (right - left) / 3;
      double x1 = left + third;
      double x2 = right - third;

      if (volume(x1) < volume(x2))
        left = x1;
      else
        right = x2;
    }

    printf("%.3f %.3f %.3f\n", left, 0.0, min(L, W) / 2.0);
  }
}
