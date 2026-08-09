#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long maximumHappinessSum(vector<int>& happiness, const int k) {
    sort(happiness.rbegin(), happiness.rend());

    long long ans = 0;

    for (int t = 0; t < k; t++) {
      ans += max(0, happiness[t] - t);
    }

    return ans;
  }
};
