#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<long long> psum;
  long long range_sum(const int l, const int r) { return psum[r + 1] - psum[l]; }

 public:
  vector<long long> maximumSegmentSum(const vector<int>& nums,
                                      const vector<int>& remove_queries) {
    const int n = nums.size();

    psum.emplace_back(0);
    for (const int x : nums) psum.emplace_back(x + psum.back());

    map<int, int> segments;
    segments[0] = n - 1;

    multiset<long long> vals;
    vals.emplace(range_sum(0, n - 1));

    vector<long long> ans;

    for (const int idx : remove_queries) {
      const auto it = prev(segments.upper_bound(idx));
      const auto [a, b] = *it;

      segments.erase(it);
      vals.erase(vals.find(range_sum(a, b)));

      if (a != b) {
        if (a == idx) {
          segments[a + 1] = b;
          vals.emplace(range_sum(a + 1, b));
        } else if (b == idx) {
          segments[a] = b - 1;
          vals.emplace(range_sum(a, b - 1));
        } else {
          segments[a] = idx - 1;
          segments[idx + 1] = b;
          vals.emplace(range_sum(a, idx - 1));
          vals.emplace(range_sum(idx + 1, b));
        }
      }

      ans.emplace_back(vals.empty() ? 0 : *vals.rbegin());
    }

    return ans;
  }
};
