#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

void solve() {
  array<pair<ld, ld>, 3> points;

  for (auto& p : points) cin >> p.first >> p.second;

  ld max_y = 0;

  for (const auto& p : points) max_y = max(max_y, p.second);

  ld ans = 0;

  const auto set_ans = [&](const pair<ld, ld>& a, const pair<ld, ld>& b) {
    if (a.second == b.second && a.second == max_y) {
      ans = hypot(a.first - b.first, a.second - b.second);
    }
  };

  set_ans(points[0], points[1]);
  set_ans(points[1], points[2]);
  set_ans(points[2], points[0]);

  cout << fixed << setprecision(12) << ans << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
