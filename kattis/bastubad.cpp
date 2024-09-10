#include <bits/stdc++.h>
using namespace std;
using ld = long double;

int main() {
  int n;

  while (cin >> n) {
    set<ld> xs;
    map<ld, tuple<ld, ld, ld>> m;

    ld A = 0, B = 0, C = 0;

    const auto eval = [&](const ld x) { return A * x * x + B * x + C; };

    while (n--) {
      ld a, b, c, t;
      cin >> a >> b >> c >> t;
      A += a;
      B += b;
      C += c;

      xs.emplace(t);
      get<0>(m[t]) += a;
      get<1>(m[t]) += b;
      get<2>(m[t]) += c;
    }

    ld ans = C;

    ld prev_x = 0;

    for (const ld x : xs) {
      while (!m.empty() && m.begin()->first < x) {
        const auto [a, b, c] = m.begin()->second;
        m.erase(m.begin());
        A -= a;
        B -= b;
        C -= c;
      }

      if (A != 0) {
        const ld vertex = -B / (2 * A);
        if (prev_x <= vertex && vertex <= x) {
          ans = max(ans, eval(vertex));
        }
      }

      ans = max(ans, eval(x));
      prev_x = x;
    }

    cout << fixed << setprecision(10) << ans << endl;
  }
}
