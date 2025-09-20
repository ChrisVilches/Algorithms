#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;

 public:
  vector<int> productQueries(const int n, const vector<vector<int>>& queries) {
    vector<int> powers;

    for (int i = 0; i < 31; i++) {
      if ((n & (1 << i)) != 0) powers.emplace_back(1 << i);
    }

    vector<int> ans;

    for (const vector<int>& query : queries) {
      const int start = query.front();
      const int end = query.back();

      long long res = 1;
      for (int i = start; i <= end; i++) {
        res *= powers[i];
        res %= mod;
      }

      ans.emplace_back(res);
    }

    return ans;
  }
};
