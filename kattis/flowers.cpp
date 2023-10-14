#include <bits/stdc++.h>
using namespace std;

double integrate(const double a, const double b, function<double(double)> f) {
  const int n = 100'000;
  const double dx = (b - a) / n;

  double total = f(a) + f(b);

  for (int i = 1; i < n; i++) {
    const double mult = i % 2 == 0 ? 2 : 4;
    total += mult * f(a + i * dx);
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
