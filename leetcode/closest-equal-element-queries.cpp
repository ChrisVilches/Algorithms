#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> solveQueries(const vector<int>& nums, const vector<int>& queries) {
    const int n = nums.size();
    vector<int> all(n, INT_MAX);

    unordered_map<int, int> last;

    for (int i = 0; i < 2 * n; i++) {
      const int x = nums[i % n];
      if (last.count(x)) all[i % n] = min(all[i % n], i - last[x]);
      last[x] = i;
    }

    last.clear();

    for (int i = 2 * n; i >= 0; i--) {
      const int x = nums[i % n];
      if (last.count(x)) all[i % n] = min(all[i % n], last[x] - i);
      last[x] = i;
    }

    vector<int> ans;

    for (const int q : queries) {
      ans.emplace_back(all[q] == n ? -1 : all[q]);
    }

    return ans;
  }
};
