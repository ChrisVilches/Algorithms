#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;
  vector<ll> cities;

  bool possible(const ll min_val, const int r, ll k) const {
    const int n = cities.size();

    queue<pair<ll, ll>> q;

    ll add = 0;

    for (int i = 0; i < n; i++) {
      if (!q.empty() && q.front().first == i) {
        add -= q.front().second;
        q.pop();
      }

      if (cities[i] + add >= min_val) continue;

      const ll diff = min_val - (cities[i] + add);

      k -= diff;
      if (k < 0) return false;

      add += diff;
      q.emplace(i + (2 * r) + 1, diff);
    }

    return true;
  }

 public:
  long long maxPower(const vector<int>& stations, const int r, const int k) {
    const int n = stations.size();
    cities.assign(stations.size(), 0);
    vector<ll> delta(n + 1, 0);

    for (int i = 0; i < n; i++) {
      const int a = max(0, i - r);
      const int b = min(n - 1, i + r);
      delta[a] += stations[i];
      delta[b + 1] -= stations[i];
    }

    ll curr = 0;

    for (int i = 0; i < n; i++) {
      curr += delta[i];
      cities[i] = curr;
    }

    ll lo = 0;
    ll hi = 1e18;

    while (lo <= hi) {
      const ll mid = (lo + hi) / 2;

      if (possible(mid, r, k)) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return hi;
  }
};
