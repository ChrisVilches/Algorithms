#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxDistance(const vector<int>& nums1, const vector<int>& nums2) {
    size_t ans = 0;

    for (size_t i = 0, j = 0; j < nums2.size(); j++) {
      while (i < nums1.size() && nums1[i] > nums2[j]) i++;

      if (i == nums1.size()) break;

      if (i <= j) ans = max(ans, j - i);
    }

    return ans;
  }
};
