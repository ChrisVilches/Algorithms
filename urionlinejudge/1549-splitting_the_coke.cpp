#include <bits/stdc++.h>

using namespace std;

double N, L, b, B, H;

inline double volume(double h) {
  double R = ((h / H) * (B - b)) + b;
  return (1 / 3.0) * M_PI * (pow(b, 2) + b * R + pow(R, 2)) * h;
}

void solve() {
  cin >> N >> L >> b >> B >> H;

  double required = L / N;
  double left = 0;
  double right = H;

  int iters = 100;

  while (iters--) {
    double mid = (left + right) / 2.0;

    if (volume(mid) < required)
      left = mid;
    else
      right = mid;
  }

  printf("%.2f\n", left);
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
