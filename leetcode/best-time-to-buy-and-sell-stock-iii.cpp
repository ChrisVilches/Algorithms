#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> get_left_accum(const vector<int>& prices) {
    vector<int> res;
    int min_val = prices.front();

    for (const int p : prices) {
      res.emplace_back(p - min_val);
      min_val = min(min_val, p);
    }

    for (int i = 1; i < (int)res.size(); i++) {
      res[i] = max(res[i], res[i - 1]);
    }

    return res;
  }

 public:
  int maxProfit(const vector<int>& prices) {
    const int n = prices.size();
    const vector<int> left = get_left_accum(prices);

    int ans = left.back();

    int max_val = 0;

    for (int i = n - 1; i >= 1; i--) {
      const int profit = max_val - prices[i] + left[i - 1];
      max_val = max(max_val, prices[i]);

      ans = max(ans, profit);
    }

    return ans;
  }
};
