#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> pivotArray(const vector<int>& nums, const int pivot) {
    vector<int> before, after;
    int pivot_count = 0;

    for (const int x : nums) {
      if (x == pivot) {
        pivot_count++;
      } else if (x < pivot) {
        before.emplace_back(x);
      } else {
        after.emplace_back(x);
      }
    }

    while (pivot_count--) before.emplace_back(pivot);

    before.insert(before.end(), after.begin(), after.end());

    return before;
  }
};
