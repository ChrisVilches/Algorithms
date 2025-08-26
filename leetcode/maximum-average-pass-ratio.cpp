#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  double maxAverageRatio(const vector<vector<int>>& classes, const int extraStudents) {
    priority_queue<tuple<double, double, double>> pq;

    const auto add = [&](const double pass, const double total) {
      const double curr_ratio = pass / total;
      const double next_ratio = (pass + 1) / (total + 1);
      pq.emplace(next_ratio - curr_ratio, pass, total);
    };

    for (const vector<int>& c : classes) {
      add(c.front(), c.back());
    }

    for (int i = 0; i < extraStudents; i++) {
      const auto [_, pass, total] = pq.top();
      pq.pop();
      add(pass + 1, total + 1);
    }

    double ans = 0;

    while (!pq.empty()) {
      const auto [_, pass, total] = pq.top();
      pq.pop();
      ans += pass / total;
    }

    return ans / classes.size();
  }
};
