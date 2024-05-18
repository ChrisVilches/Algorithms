#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<string> summaryRanges(vector<int>& nums) {
    vector<pair<int, int>> ranges;

    for (const int x : nums) {
      if (ranges.empty() || ranges.back().second != x - 1) {
        ranges.emplace_back(x, x);
      }

      ranges.back().second = x;
    }

    vector<string> result;

    for (const auto& [a, b] : ranges) {
      stringstream ss;
      if (a == b) {
        ss << a;
      } else {
        ss << a << "->" << b;
      }
      result.emplace_back(ss.str());
    }

    return result;
  }
};
