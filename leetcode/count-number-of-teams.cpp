#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numTeams(const vector<int>& rating) {
    const int n = rating.size();

    vector<int> left_gt(n, 0), right_gt(n, 0);
    vector<int> left_lt(n, 0), right_lt(n, 0);

    for (int i = 1; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        if (rating[j] > rating[i]) right_gt[i]++;
        if (rating[j] < rating[i]) right_lt[i]++;
      }
      for (int j = i - 1; j >= 0; j--) {
        if (rating[j] > rating[i]) left_gt[i]++;
        if (rating[j] < rating[i]) left_lt[i]++;
      }
    }

    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
      ans += left_gt[i] * right_lt[i];
      ans += left_lt[i] * right_gt[i];
    }

    return ans;
  }
};
