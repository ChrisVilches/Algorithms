#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    const size_t n = g.size();
    const size_t m = s.size();

    int ans = 0;

    for (size_t i = 0, j = 0; i < n; i++) {
      while (j < m && g[i] > s[j]) j++;
      if (j >= m) break;
      j++;
      ans++;
    }

    return ans;
  }
};
