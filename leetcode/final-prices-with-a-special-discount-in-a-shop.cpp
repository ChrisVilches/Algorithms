#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> finalPrices(const vector<int>& prices) {
    const int n = prices.size();
    stack<int> s{{0}};
    vector<int> ans(n);

    for (int i = n - 1; i >= 0; i--) {
      while (prices[i] < s.top()) s.pop();

      ans[i] = prices[i] - s.top();
      s.emplace(prices[i]);
    }

    return ans;
  }
};
