#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findTheWinner(const int n, const int k) {
    vector<int> nums(n);
    iota(nums.begin(), nums.end(), 1);

    int i = 0;

    while (nums.size() > 1) {
      i += k - 1;
      i %= nums.size();
      nums.erase(nums.begin() + i);
    }

    return nums.front();
  }
};
