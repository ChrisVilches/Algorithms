#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  while (cin >> n) {
    map<double, vector<pair<double, double>>> events;

    for (int i = 0; i < n; i++) {
      double x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      events[x1].emplace_back(y1, 1);
      events[x1].emplace_back(y2, -1);
      events[x2].emplace_back(y1, -1);
      events[x2].emplace_back(y2, 1);
    }

    map<double, int> y_mapping;

    double ans = 0;
    double prev_x = events.begin()->first;

    for (const auto& [x, ev] : events) {
      int curr = 0;
      double prev_start = 0;

      for (const auto& [y, d] : y_mapping) {
        if (curr == 0) prev_start = y;
        curr += d;
        if (curr == 0) {
          ans += (x - prev_x) * (y - prev_start);
        }
      }

      for (const auto& [y, d] : ev) {
        y_mapping[y] += d;
        if (y_mapping[y] == 0) y_mapping.erase(y);
      }

      prev_x = x;
    }

    cout << fixed << setprecision(2) << ans << endl;
  }
}
