#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    set<int> a{nums1.begin(), nums1.end()};
    set<int> result;
    for (const int x : nums2) {
      if (a.count(x)) result.emplace(x);
    }
    return {result.begin(), result.end()};
  }
};
