#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long getDescentPeriods(const vector<int>& prices) {
    const int n = prices.size();

    long long ans = 0;
    long long count = 1;

    for (int i = 1; i < n; i++) {
      if (prices[i - 1] - 1 == prices[i]) {
        count++;
      } else {
        ans += (count * (count + 1)) / 2;
        count = 1;
      }
    }

    ans += (count * (count + 1)) / 2;
    return ans;
  }
};
