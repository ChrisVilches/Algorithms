#include <bits/stdc++.h>
using namespace std;

vector<double> multiply_polynomial(const vector<double>& p1, const vector<double>& p2) {
  vector<double> result(p1.size() + p2.size() - 1);
  for (int i = 0; i < (int)p1.size(); i++)
    for (int j = 0; j < (int)p2.size(); j++) result[i + j] += p1[i] * p2[j];
  return result;
}

struct Function {
  double integrate(const double a, const double b) const {
    double total = 0;

    for (int i = 0; i < (int)squared_polynomial.size(); i++) {
      total += squared_polynomial[i] * pow(b, i + 1) / (i + 1);
      total -= squared_polynomial[i] * pow(a, i + 1) / (i + 1);
    }

    return M_PI * total;
  }

  static Function from_stdin(const int n) {
    Function fn;
    vector<double> polynomial(n);
    for (double& v : polynomial) cin >> v;

    fn.squared_polynomial = multiply_polynomial(polynomial, polynomial);
    return fn;
  }

 private:
  vector<double> squared_polynomial;
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
