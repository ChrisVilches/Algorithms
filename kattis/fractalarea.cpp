#include <bits/stdc++.h>

using namespace std;

double area(double r) { return r * r * M_PI; }

double fractal_area(double r, int n) {
  if (n == 1) return area(r);

  double result = area(r) + 4 * fractal_area(r / 2, 1);

  double circles = 4;
  r = r / 4;

  for (int i = 3; i <= n; i++) {
    circles *= 3;
    result += (circles * area(r));
    r /= 2;
  }
  return result;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    double r;
    int n;
    cin >> r >> n;
    printf("%.20f\n", fractal_area(r, n));
  }
}
