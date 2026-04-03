#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minimumCost(vector<int>& cost) {
    sort(cost.rbegin(), cost.rend());

    int ans = 0;

    while (cost.size() % 3 != 0) {
      ans += cost.back();
      cost.pop_back();
    }

    for (size_t i = 0; i < cost.size(); i += 3) {
      ans += cost[i];
      ans += cost[i + 1];
    }

    return ans;
  }
};
