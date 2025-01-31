#include <bits/stdc++.h>
using namespace std;
#define x front()
#define y back()

class Solution {
  using ll = long long;

 public:
  int minimumLines(vector<vector<int>>& prices) {
    if (prices.size() <= 1) return 0;

    sort(prices.begin(), prices.end());

    int ans = 1;

    for (int i = 2; i < prices.size(); i++) {
      const ll dx1 = prices[i - 1].x - prices[i - 2].x;
      const ll dx2 = prices[i].x - prices[i - 1].x;
      const ll dy1 = prices[i - 1].y - prices[i - 2].y;
      const ll dy2 = prices[i].y - prices[i - 1].y;
      ans += dx2 * dy1 != dy2 * dx1;
    }

    return ans;
  }
};
