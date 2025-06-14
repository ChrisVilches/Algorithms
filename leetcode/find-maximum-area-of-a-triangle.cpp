#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;

 public:
  long long maxArea(const vector<vector<int>>& coords) {
    ll min_x = 1e9, max_x = 0;
    ll min_y = 1e9, max_y = 0;

    unordered_map<ll, pair<ll, ll>> x_pairs, y_pairs;

    for (const auto& point : coords) {
      const ll x = point.front();
      const ll y = point.back();
      max_x = max(max_x, x);
      min_x = min(min_x, x);
      max_y = max(max_y, y);
      min_y = min(min_y, y);

      if (!x_pairs.count(x)) x_pairs[x] = {1e9, 0};
      if (!y_pairs.count(y)) y_pairs[y] = {1e9, 0};

      x_pairs[x].first = min(x_pairs[x].first, y);
      x_pairs[x].second = max(x_pairs[x].second, y);

      y_pairs[y].first = min(y_pairs[y].first, x);
      y_pairs[y].second = max(y_pairs[y].second, x);
    }

    ll ans = 0;

    for (const auto& [y, y_pair] : y_pairs) {
      const auto [lo, hi] = y_pair;
      const ll base = hi - lo;
      ans = max({ans, base * abs(y - min_y), base * abs(y - max_y)});
    }

    for (const auto& [x, x_pair] : x_pairs) {
      const auto [lo, hi] = x_pair;
      const ll base = hi - lo;
      ans = max({ans, base * abs(x - min_x), base * abs(x - max_x)});
    }

    if (ans == 0) return -1;

    return ans;
  }
};
