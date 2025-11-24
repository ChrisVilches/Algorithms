#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> countRectangles(const vector<vector<int>>& rectangles,
                              const vector<vector<int>>& points) {
    vector<tuple<int, int, int>> events;
    vector<int> counts(107, 0);

    for (const vector<int>& rect : rectangles) {
      const int l = rect.front();
      const int h = rect.back();
      events.emplace_back(l, INT_MAX, h);

      for (int i = 0; i <= h; i++) counts[i]++;
    }

    for (size_t i = 0; i < points.size(); i++) {
      const vector<int>& p = points[i];
      events.emplace_back(p.front(), i, p.back());
    }

    sort(events.begin(), events.end());

    vector<int> ans(points.size());

    for (const auto& [_, idx, y] : events) {
      if (idx == INT_MAX) {
        for (int i = 0; i <= y; i++) counts[i]--;
      } else {
        ans[idx] = counts[y];
      }
    }

    return ans;
  }
};
