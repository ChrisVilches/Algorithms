#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> canSeePersonsCount(const vector<int>& heights) {
    const int n = heights.size();

    vector<int> ans(n, 0);
    stack<int> s;

    for (int i = n - 1; i >= 0; i--) {
      while (!s.empty() && heights[i] > heights[s.top()]) {
        ans[i]++;
        s.pop();
      }

      ans[i] += !s.empty();
      s.emplace(i);
    }

    return ans;
  }
};
