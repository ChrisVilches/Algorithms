#include <bits/stdc++.h>
using namespace std;

double integrate(const double a, const double b, function<double(double)> f) {
  const int n = 100'000;
  const double dx = (b - a) / n;

  double total = 0;

  for (int i = 0; i <= n; i++) {
    const double x = a + i * dx;
    double mult;

    if (i == 0 || i == n) {
      mult = 1.0;
    } else if (i % 2 == 0) {
      mult = 2.0;
    } else {
      mult = 4.0;
    }

    total += mult * f(x);
  }

  return (dx / 3.0) * total;
}

int main() {
  double V;
  int N;
  cin >> V >> N;
  int idx = -1;
  double diff = DBL_MAX;

  for (int i = 0; i < N; i++) {
    double a, b, h;
    cin >> a >> b >> h;
    const double vol = integrate(0, h, [&](const double x) {
      const double r = a * exp(-x * x) + b * sqrt(x);
      return M_PI * r * r;
    });
    const double curr_diff = fabs(vol - V);
    if (curr_diff < diff) {
      diff = curr_diff;
      idx = i;
    }
  }

  cout << idx << endl;
}
