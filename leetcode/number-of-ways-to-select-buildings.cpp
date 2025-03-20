#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;

 public:
  ll numberOfWays(const string s) {
    const int n = s.size();

    ll right_zeros_accum = 0;
    ll right_ones_accum = 0;

    vector<ll> right_zeros(n, 0), right_ones(n, 0);

    for (int i = n - 1; i >= 0; i--) {
      if (s[i] == '0') {
        right_zeros_accum++;
        right_ones[i] = right_ones_accum;
      } else {
        right_ones_accum++;
        right_zeros[i] = right_zeros_accum;
      }
    }

    vector<ll> psum_zeros{0}, psum_ones{0};

    for (const ll x : right_zeros) psum_zeros.emplace_back(psum_zeros.back() + x);
    for (const ll x : right_ones) psum_ones.emplace_back(psum_ones.back() + x);

    ll ans = 0;

    for (int i = 0; i < n - 2; i++) {
      if (s[i] == '0') {
        ans += psum_zeros[n] - psum_zeros[i + 1];
      } else {
        ans += psum_ones[n] - psum_ones[i + 1];
      }
    }

    return ans;
  }
};
