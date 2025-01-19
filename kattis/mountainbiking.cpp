#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  double g;
  cin >> n >> g;

  vector<pair<double, double>> slopes(n);

  for (auto& [dist, theta] : slopes) {
    cin >> dist >> theta;
    theta *= M_PI / 180;
  }

  for (int i = 0; i < n; i++) {
    double v0 = 0;

    for (int j = i; j < n; j++) {
      const auto [dist, theta] = slopes[j];

      const double acc = cos(theta) * g;
      const double a = 0.5 * acc;
      const double b = v0;
      const double c = -dist;

      const double t = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

      const double vf = v0 + acc * t;

      v0 = vf;
    }

    cout << fixed << setprecision(9) << v0 << endl;
  }
}
