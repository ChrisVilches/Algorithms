#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minCostToMoveChips(const vector<int>& position) {
    array<int, 2> sum{0, 0};

    for (const int p : position) {
      sum[p % 2]++;
    }

    return min(sum.front(), sum.back());
  }
};
