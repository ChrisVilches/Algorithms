#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;
  const ll mod = 1e9 + 7;

 public:
  int peopleAwareOfSecret(const int n, const int delay, const int forget) {
    vector<ll> ans(n, 0), deltas(n * 2, 0);

    ans.front() = 1;

    ll curr = 0;

    for (int i = 0; i < n; i++) {
      curr = (curr + deltas[i] + mod) % mod;
      ans[i] += curr;
      deltas[i + delay] += ans[i];
      deltas[i + forget] -= ans[i];
    }

    fill(deltas.begin(), deltas.end(), 0);

    for (int i = 0; i < n; i++) {
      deltas[i + 1] += ans[i];
      deltas[i + forget] -= ans[i];
    }

    curr = 0;

    for (int i = 0; i < n; i++) {
      curr = (curr + deltas[i] + mod) % mod;
      ans[i] += curr;
    }

    return ans.back() % mod;
  }
};
