#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    map<int, int> freq1, freq2;

    for (const int x : nums1) freq1[x]++;
    for (const int x : nums2) freq2[x]++;

    multiset<int> result;

    for (const auto& [val, f] : freq1) {
      int min_f = min(f, freq2[val]);

      while (min_f--) {
        result.emplace(val);
      }
    }

    return {result.begin(), result.end()};
  }
};
