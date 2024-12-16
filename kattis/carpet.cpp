#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
const double turn = 2 * M_PI;

int main() {
  double a, b, c;

  while (cin >> a >> b >> c) {
    const vector<pair<double, double>> pairs{{a, b}, {a, c}, {b, c}};

    double lo = 0;
    double hi = 1000;

    bool found = false;

    for (const auto& [x, y] : pairs) {
      hi = min(hi, x + y);
    }

    for (int iter = 0; iter < 150; iter++) {
      const double l = (lo + hi) / 2;

      double total_angle = 0;

      for (const auto& [x, y] : pairs) {
        total_angle += acos((x * x + y * y - l * l) / (2 * x * y));
      }

      if (fabs(total_angle - turn) < EPS) {
        found = true;
      }

      if (!isnan(total_angle) && total_angle > turn) {
        hi = l;
      } else {
        lo = l;
      }
    }

    if (found) {
      const double area = pow(lo, 2) * sqrt(3) / 4;
      cout << fixed << setprecision(9) << area << endl;
    } else {
      cout << -1 << endl;
    }
  }
}
