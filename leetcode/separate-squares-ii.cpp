#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ld = long double;

 public:
  double separateSquares(const vector<vector<int>>& squares) {
    map<ld, vector<pair<ld, ld>>> events;

    for (const auto& sq : squares) {
      const ld side = sq.back();
      const ld x1 = sq[0];
      const ld y1 = sq[1];
      const ld x2 = x1 + side;
      const ld y2 = y1 + side;
      events[y1].emplace_back(x1, 1);
      events[y1].emplace_back(x2, -1);
      events[y2].emplace_back(x1, -1);
      events[y2].emplace_back(x2, 1);
    }

    map<ld, int> x_mapping;

    ld total = 0;
    ld prev_y = events.begin()->first;

    vector<tuple<ld, ld, ld>> sections;

    for (const auto& [y, ev] : events) {
      int curr = 0;
      ld prev_start = 0;
      ld total_x_length = 0;

      for (const auto& [x, d] : x_mapping) {
        if (curr == 0) prev_start = x;
        curr += d;
        if (curr == 0) total_x_length += x - prev_start;
      }

      sections.emplace_back(total_x_length, y - prev_y, prev_y);

      for (const auto& [x, d] : ev) {
        x_mapping[x] += d;
        if (x_mapping[x] == 0) x_mapping.erase(x);
      }

      prev_y = y;
    }

    ld target = 0;
    for (const auto& [dx, dy, _] : sections) target += dx * dy;
    target /= 2;

    ld curr = 0;

    for (const auto& [dx, dy, y] : sections) {
      const ld area = dx * dy;

      if (curr + area >= target) {
        return y + (target - curr) / dx;
      }

      curr += area;
    }

    assert(false);
  }
};
