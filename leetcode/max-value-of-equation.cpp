#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findMaxValueOfEquation(const vector<vector<int>>& points, const int k) {
    priority_queue<pair<int, int>> pq;

    int ans = INT_MIN;

    for (const auto& p : points) {
      const int x = p.front();
      const int y = p.back();

      while (!pq.empty() && x - pq.top().second > k) {
        pq.pop();
      }

      if (!pq.empty()) {
        ans = max(ans, x + y + pq.top().first);
      }

      pq.emplace(y - x, x);
    }

    return ans;
  }
};
