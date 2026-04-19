#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;

 public:
  vector<int> sumAndMultiply(const string s, const vector<vector<int>>& queries) {
    vector<int> psum{0}, nonzeros{0}, concat{0};
    vector<int> pow10{1};

    for (size_t i = 0; i < s.size(); i++) {
      pow10.emplace_back((10LL * pow10.back()) % mod);
    }

    for (const char c : s) {
      psum.emplace_back(psum.back() + c - '0');

      const int digit = c - '0';

      nonzeros.emplace_back(nonzeros.back() + (digit != 0));

      if (digit == 0) {
        concat.emplace_back(concat.back());
      } else {
        concat.emplace_back((10LL * concat.back() + digit) % mod);
      }
    }

    vector<int> ans;

    for (const vector<int>& q : queries) {
      const int l = q.front();
      const int r = q.back();
      const int digits_count = nonzeros[r + 1] - nonzeros[l];
      const int sum = psum[r + 1] - psum[l];
      const int subtract = (1LL * concat[l] * pow10[digits_count]) % mod;
      const int concat_val = concat[r + 1] - subtract + mod;
      ans.emplace_back((1LL * concat_val * sum) % mod);
    }

    return ans;
  }
};
