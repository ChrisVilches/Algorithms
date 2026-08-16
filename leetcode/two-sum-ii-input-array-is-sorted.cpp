#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> twoSum(const vector<int>& numbers, const int target) {
    const int n = numbers.size();

    for (int i = 0; i < n - 1; i++) {
      const int complement = target - numbers[i];

      const auto it = lower_bound(numbers.begin() + i + 1, numbers.end(), complement);

      if (it == numbers.end()) continue;
      if (*it != complement) continue;

      const int idx = distance(numbers.begin(), it);
      return {i + 1, idx + 1};
    }

    assert(false);
  }
};
