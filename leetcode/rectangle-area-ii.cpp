#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int rectangleArea(vector<vector<int>>& rectangles) {
    set<int> xs, ys;
    for (const auto& rect : rectangles) {
      xs.emplace(rect[0]);
      xs.emplace(rect[2]);
      ys.emplace(rect[1]);
      ys.emplace(rect[3]);
    }

    set<vector<int>> small1, small2;

    for (const auto& rect : rectangles) {
      int prev_x = rect[0];
      for (const auto x : xs) {
        if (x <= rect[0] || rect[2] < x) continue;
        small1.emplace(vector<int>{prev_x, rect[1], x, rect[3]});
        prev_x = x;
      }
    }

    for (const auto& rect : small1) {
      int prev_y = rect[1];
      for (const auto y : ys) {
        if (y <= rect[1] || rect[3] < y) continue;
        small2.emplace(vector<int>{rect[0], prev_y, rect[2], y});
        prev_y = y;
      }
    }

    const long long MOD = 1e9 + 7;
    long long total = 0;

    for (const auto& rect : small2) {
      const long long a = rect[2] - rect[0];
      const long long b = rect[3] - rect[1];
      total += a * b;
      total %= MOD;
    }

    return (int)total;
  }
};
