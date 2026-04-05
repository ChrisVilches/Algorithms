#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minimumDeletions(const vector<int>& nums) {
    const int n = nums.size();

    int a = distance(nums.begin(), min_element(nums.begin(), nums.end()));
    int b = distance(nums.begin(), max_element(nums.begin(), nums.end()));
    if (a > b) swap(a, b);

    return min({n - b + a + 1, b + 1, n - a});
  }
};
