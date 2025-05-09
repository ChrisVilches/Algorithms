#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minOperations(const vector<int>& nums, const int k) {
    set<int> s{nums.begin(), nums.end()};

    if (*s.begin() < k) return -1;
    s.erase(k);
    return s.size();
  }
};
