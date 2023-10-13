#include <bits/stdc++.h>
using namespace std;

vector<double> quadratic_solutions(const double a, const double b, const double c) {
  if (b * b - 4 * a * c < 0) return {};
  return vector<double>{(-b + sqrt(b * b - 4 * a * c)) / (2 * a),
                        (-b - sqrt(b * b - 4 * a * c)) / (2 * a)};
}

int main() {
  double b0, b1, b2, b3;
  double t0, t1, t2, t3;

  while (cin >> b0 >> b1 >> b2 >> b3 >> t0 >> t1 >> t2 >> t3) {
    const double d0 = t0 - b0;
    const double d1 = t1 - b1;
    const double d2 = t2 - b2;
    const double d3 = t3 - b3;

    double max_dist = -1e9;
    double min_dist = 1e9;

    max_dist = max({max_dist, d0, d0 + d1 + d2 + d3});
    min_dist = min({min_dist, d0, d0 + d1 + d2 + d3});

    const auto derivative_zeros = quadratic_solutions(d3 * 3, d2 * 2, d1);

    for (const double x : derivative_zeros) {
      if (x < 0 || x > 1) continue;

      const double dist = d0 + (d1 * x) + (d2 * x * x) + (d3 * x * x * x);
      max_dist = max(max_dist, dist);
      min_dist = min(min_dist, dist);
    }

    cout << fixed << setprecision(9) << max_dist - min_dist << endl;
  }
}
