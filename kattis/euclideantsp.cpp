#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

int n;
ld p, s, v;

ld calc(const ld c) {
  const ld run = n * pow(log2(n), c * sqrt(2)) / (p * 1e9);
  const ld fly = (s * (1 + 1 / c)) / v;
  return run + fly;
}

int main() {
  cin >> n >> p >> s >> v;

  ld lo = 1e-3;
  ld hi = 1e3;

  for (int it = 0; it < 500; it++) {
    const ld third = (hi - lo) / 3;
    const ld t1 = lo + third;
    const ld t2 = hi - third;

    if (calc(t1) < calc(t2)) {
      hi = t2;
    } else {
      lo = t1;
    }
  }

  cout << fixed << setprecision(12) << calc(lo) << " " << lo << endl;
}
