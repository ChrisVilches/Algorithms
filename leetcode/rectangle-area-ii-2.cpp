#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;
  const ll mod = 1e9 + 7;

 public:
  int rectangleArea(const vector<vector<int>>& rectangles) {
    map<ll, vector<pair<ll, ll>>> events;

    for (const auto& rect : rectangles) {
      const ll x1 = rect[0];
      const ll y1 = rect[1];
      const ll x2 = rect[2];
      const ll y2 = rect[3];
      events[x1].emplace_back(y1, 1);
      events[x1].emplace_back(y2, -1);
      events[x2].emplace_back(y1, -1);
      events[x2].emplace_back(y2, 1);
    }

    map<ll, int> y_mapping;

    ll ans = 0;
    ll prev_x = events.begin()->first;

    for (const auto& [x, ev] : events) {
      int curr = 0;
      ll prev_start = 0;

      for (const auto& [y, d] : y_mapping) {
        if (curr == 0) prev_start = y;
        curr += d;
        if (curr == 0) {
          ans += (x - prev_x) * (y - prev_start);
          ans %= mod;
        }
      }

      for (const auto& [y, d] : ev) {
        y_mapping[y] += d;
        if (y_mapping[y] == 0) y_mapping.erase(y);
      }

      prev_x = x;
    }

    return ans;
  }
};
