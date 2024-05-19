#include <bits/stdc++.h>
using namespace std;

int main() {
  int T, N;
  cin >> T;
  for (int t = 0; t < T; t++) {
    cin >> N;
    vector<pair<double, double>> events;
    for (int i = 0; i < N; i++) {
      double y;
      double x1, x2, r;
      cin >> x1 >> y;
      cin >> x2 >> y;
      cin >> r;
      assert(r != 0);
      if (x1 > x2) swap(x1, x2);
      events.emplace_back(x1, r);
      events.emplace_back(x2, 1 / r);
    }
    sort(events.begin(), events.end());
    double curr_x = -INFINITY;
    double curr_r = 1;

    cout << fixed << setprecision(3);

    vector<tuple<double, double, double>> result;

    for (const auto& [x, r] : events) {
      result.emplace_back(curr_x, x, curr_r);
      curr_r *= r;
      curr_x = x;
    }

    sort(result.begin(), result.end());

    if (t > 0) cout << endl;

    cout << 1 + N * 2 << endl;

    for (const auto& [x0, x1, r] : result) {
      cout << x0 << " " << x1 << " " << r << endl;
    }

    cout << curr_x << " +inf " << curr_r << endl;
  }
}
