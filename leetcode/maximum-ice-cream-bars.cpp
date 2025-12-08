#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxIceCream(const vector<int>& costs, int coins) {
    const int max_cost = 100'001;
    vector<int> freq(max_cost, 0);

    for (const int c : costs) freq[c]++;

    int ans = 0;

    for (int cost = 1; cost < max_cost; cost++) {
      if (coins < cost) break;

      const int buy = min(freq[cost], coins / cost);

      ans += buy;

      coins -= buy * cost;
    }

    return ans;
  }
};
