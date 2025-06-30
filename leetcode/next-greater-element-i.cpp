#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> nextGreaterElement(const vector<int>& nums1, const vector<int>& nums2) {
    unordered_map<int, int> idx;

    for (const int x : nums1) {
      idx[x] = idx.size();
    }

    stack<int> s;
    const int n = nums2.size();
    vector<int> ans(nums1.size(), -1);

    for (int i = n - 1; i >= 0; i--) {
      const int x = nums2[i];
      while (!s.empty() && nums2[s.top()] <= x) s.pop();

      if (idx.count(x) && !s.empty()) {
        ans[idx[x]] = nums2[s.top()];
      }

      s.push(i);
    }

    return ans;
  }
};
