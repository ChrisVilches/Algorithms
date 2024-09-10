#include <bits/stdc++.h>
using namespace std;
using ld = long double;

int main() {
  int n;

  while (cin >> n) {
    map<ld, tuple<ld, ld, ld>> events;

    ld A = 0, B = 0, C = 0;

    const auto eval = [&](const ld x) { return A * x * x + B * x + C; };

    while (n--) {
      ld a, b, c, t;
      cin >> a >> b >> c >> t;
      A += a;
      B += b;
      C += c;

      get<0>(events[t]) += a;
      get<1>(events[t]) += b;
      get<2>(events[t]) += c;
    }

    ld ans = C;

    ld prev_x = 0;

    for (const auto& [x, abc] : events) {
      const auto [a, b, c] = abc;

      if (A != 0) {
        const ld vertex = -B / (2 * A);
        if (prev_x <= vertex && vertex <= x) {
          ans = max(ans, eval(vertex));
        }
      }

      ans = max(ans, eval(x));

      A -= a;
      B -= b;
      C -= c;

      prev_x = x;
    }

    cout << fixed << setprecision(10) << ans << endl;
  }
}
