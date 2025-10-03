#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll c2(const ll n) { return (n * (n - 1)) / 2; }

class Solution {
  const ll mod = 1e9 + 7;

 public:
  int countTrapezoids(const vector<vector<int>>& points) {
    unordered_map<int, int> counts;
    for (const vector<int>& point : points) counts[point.back()]++;

    vector<ll> combinations;
    for (const auto& [_, count] : counts) combinations.emplace_back(c2(count));

    ll ans = 0;
    ll sum = 0;

    for (const ll x : combinations) sum = (sum + x) % mod;

    for (const ll x : combinations) {
      sum = (sum - x + mod) % mod;

      ans += x * sum;
      ans %= mod;
    }

    return ans;
  }
};
