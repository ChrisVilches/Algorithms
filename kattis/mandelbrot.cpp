#include <bits/stdc++.h>
using namespace std;

struct Complex {
  double re, imag;

  Complex operator+(const Complex n) const { return {re + n.re, imag + n.imag}; }
  Complex square() const { return {re * re - imag * imag, 2 * re * imag}; }
  double modulus() const { return sqrt(re * re + imag * imag); }
};

int main() {
  int r;
  int case_n = 1;

  Complex c;

  while (cin >> c.re >> c.imag >> r) {
    Complex z{0, 0};

    for (int it = 0; it < r; it++) {
      z = z.square() + c;
    }

    const bool converge = fabs(z.modulus()) <= 2;

    cout << "Case " << case_n << ": " << (converge ? "IN" : "OUT") << endl;

    case_n++;
  }
}
