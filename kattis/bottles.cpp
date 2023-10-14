#include <bits/stdc++.h>
using namespace std;

struct Function {
  double integrate(const double a, const double b) const {
    const int n = simpson_n;
    const double dx = (b - a) / n;

    double total = f(a) + f(b);

    for (int i = 1; i < n; i++) {
      const double mult = i % 2 == 0 ? 2 : 4;
      total += mult * f(a + i * dx);
    }

    return (dx / 3.0) * total;
  }

  static Function from_stdin(const int n) {
    Function fn;
    fn.polynomial.resize(n);
    for (double& v : fn.polynomial) cin >> v;
    return fn;
  }

 private:
  vector<double> polynomial;
  const int simpson_n = 2600;

  double f(const double x) const {
    double sum = 0;
    for (int i = 0; i < (int)polynomial.size(); i++) sum += pow(x, i) * polynomial[i];
    return M_PI * pow(sum, 2);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout << fixed << setprecision(2) << endl;

  int N;
  int t = 1;

  while (cin >> N) {
    const Function fn = Function::from_stdin(N + 1);

    double x_low, x_hi, inc;
    cin >> x_low >> x_hi >> inc;

    const double full_vol = fn.integrate(x_low, x_hi);

    cout << "Case " << t++ << ": " << full_vol << endl;

    if (full_vol < inc) {
      cout << "insufficient volume" << endl;
      continue;
    }

    for (int mark = 1; mark <= 8; mark++) {
      double lo = x_low;
      double hi = x_hi;

      int iters = 100;
      double vol;

      while (iters--) {
        const double x = (lo + hi) / 2;
        vol = fn.integrate(x_low, x);

        if (vol < mark * inc) {
          lo = x;
        } else {
          hi = x;
        }
      }

      if (vol + 0.01 < mark * inc) break;

      cout << lo - x_low << " ";
    }
    cout << endl;
  }
}
