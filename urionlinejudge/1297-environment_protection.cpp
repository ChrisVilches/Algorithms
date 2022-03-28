#include <bits/stdc++.h>
using namespace std;

int W, D, A, K;

struct Function {
  double limit_min_value;

  double integrate(const double a, const double b) const {
    const int n = simpson_n;
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

  static Function from_stdin(const int k) {
    Function fn;
    fn.k = k;

    for (int i = 0; i < k + 1; i++) cin >> fn.P[i];
    for (int i = 0; i < k + 1; i++) cin >> fn.Q[i];
    return fn;
  }

 private:
  array<int, 10> P, Q;
  const int simpson_n = 2600;
  int k;

  double f(double x) const {
    double p = 0, q = 0;

    for (int i = 0; i < k + 1; i++) {
      p += P[i] * pow(x, i);
      q += Q[i] * pow(x, i);
    }

    return max(p / q, limit_min_value);
  }
};

void solve() {
  Function y1 = Function::from_stdin(K);
  Function y2 = Function::from_stdin(K);

  double lo = 0;
  double hi = D;

  auto get_area = [&](const double x) {
    y1.limit_min_value = -x;
    y2.limit_min_value = -x;
    return y1.integrate(0, W) - y2.integrate(0, W);
  };

  while (hi - lo > 0.000001) {
    const double mid = (lo + hi) / 2.0;

    const double area = get_area(mid);

    if (area < A) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  cout << fixed << setprecision(5) << (lo + hi) / 2 << '\n';
}

int main() {
  while (cin >> W >> D >> A >> K) solve();
}
