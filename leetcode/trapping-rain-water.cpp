#include <bits/stdc++.h>
using namespace std;

class Solution {
  using tiii = tuple<int, int, int>;

 public:
  int trap(vector<int>& height) {
    priority_queue<tiii, vector<tiii>, greater<tiii>> q;
    int ans = 0;

    for (int i = 0; i < (int)height.size(); i++) {
      const int h = height[i];

      while (!q.empty()) {
        const auto [floor, top, x] = q.top();

        if (h <= floor) break;

        q.pop();

        ans += (i - x - 1) * (min(h, top) - floor);

        if (top > h) {
          q.emplace(h, top, x);
        }
      }

      q.emplace(0, h, i);
    }

    return ans;
  }
};
