#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int leastBricks(const vector<vector<int>>& wall) {
    unordered_map<long long, int> count;

    for (const vector<int>& row : wall) {
      long long pos = 0;
      for (size_t i = 0; i < row.size() - 1; i++) {
        pos += row[i];
        count[pos]++;
      }
    }

    int ans = wall.size();

    for (const vector<int>& row : wall) {
      long long pos = 0;
      for (size_t i = 0; i < row.size() - 1; i++) {
        pos += row[i];
        ans = min(ans, static_cast<int>(wall.size()) - count[pos]);
      }
    }

    return ans;
  }
};
