#include <bits/stdc++.h>
using namespace std;

class Solution {
  set<pair<long long, int>> s;
  vector<long long> values;
  vector<int> prev, next;

  bool has_prev_bad(const int idx) const {
    return prev[idx] != -1 && values[prev[idx]] > values[idx];
  }

  bool has_next_bad(const int idx) const {
    return next[idx] != -1 && values[idx] > values[next[idx]];
  }

 public:
  int minimumPairRemoval(const vector<int>& nums) {
    prev.resize(nums.size());
    next.resize(nums.size());
    for (const int x : nums) values.emplace_back(x);

    iota(prev.begin(), prev.end(), -1);
    iota(next.begin(), next.end(), 1);
    next.back() = -1;

    int bad = 0;

    for (size_t i = 0; i < nums.size() - 1; i++) {
      bad += nums[i] > nums[i + 1];
      s.emplace(nums[i] + nums[i + 1], i);
    }

    int ans = 0;

    for (; bad > 0; ans++) {
      const auto [sum, i] = s.extract(s.begin()).value();
      const int j = next[i];

      bad -= values[i] > values[j];

      if (prev[i] != -1) {
        const int h = prev[i];
        s.erase({values[h] + values[i], h});
        s.emplace(values[h] + sum, h);
      }

      if (next[j] != -1) {
        const int k = next[j];
        s.erase({values[j] + values[k], j});
        s.emplace(sum + values[k], i);
      }

      const bool prev_bad = has_prev_bad(i);
      const bool next_bad = has_next_bad(j);

      next[i] = next[j];
      if (next[i] != -1) prev[next[i]] = i;
      values[i] = sum;

      const bool prev_bad2 = has_prev_bad(i);
      const bool next_bad2 = has_next_bad(i);

      bad -= prev_bad && !prev_bad2;
      bad += !prev_bad && prev_bad2;
      bad -= next_bad && !next_bad2;
      bad += !next_bad && next_bad2;
    }

    return ans;
  }
};
