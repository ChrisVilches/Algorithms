#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int removeCoveredIntervals(vector<vector<int>>& intervals) {
    int count = intervals.size();

    sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
      if (a.front() == b.front()) return a.back() > b.back();
      return a.front() < b.front();
    });

    priority_queue<int> pq;

    for (const auto& interval : intervals) {
      while (!pq.empty() && pq.top() < interval.front()) pq.pop();

      if (!pq.empty()) {
        const int right = pq.top();
        count -= interval.back() <= right;
      }

      pq.emplace(interval.back());
    }

    return count;
  }
};
