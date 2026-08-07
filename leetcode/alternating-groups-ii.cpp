#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numberOfAlternatingGroups(const vector<int>& colors, const int k) {
    int ans = 0;

    int prev = -1;
    int curr = 0;

    for (size_t i = 0; i < colors.size() + k - 1; i++) {
      const int x = colors[i % colors.size()];

      if (x == prev) {
        curr = 1;
      } else {
        curr++;
      }

      if (curr >= k) ans++;

      prev = x;
    }

    return ans;
  }
};
