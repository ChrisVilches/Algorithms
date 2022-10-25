#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool canReach(string s, int minJump, int maxJump) {
    set<int> true_idx;

    const auto range_has_true = [&](const int lo, const int hi) -> bool {
      const auto it = true_idx.lower_bound(lo);
      if (it == true_idx.end()) return false;
      return *it <= hi;
    };

    if (s.back() == '0') {
      true_idx.emplace(s.size() - 1);
    }

    for (int i = s.size() - 2; i >= 0; i--) {
      if (s[i] == '1') continue;

      if (range_has_true(i + minJump, i + maxJump)) {
        true_idx.insert(i);
      }
    }

    return range_has_true(0, 0);
  }
};
