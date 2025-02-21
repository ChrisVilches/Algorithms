#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ld = long double;

 public:
  double separateSquares(const vector<vector<int>>& squares) {
    const ld total = accumulate(
        squares.begin(), squares.end(), (ld)0,
        [&](const ld sum, const auto& vec) { return sum + (ld)vec.back() * vec.back(); });

    const auto get_area_below = [&](const ld y) -> ld {
      ld total = 0;
      for (const auto& sq : squares) {
        const ld side = sq.back();
        const ld y0 = sq[1];
        const ld y1 = y0 + side;
        if (y1 <= y) {
          total += side * side;
        } else {
          const ld dy = max(y - y0, (ld)0);
          total += side * dy;
        }
      }
      return total;
    };

    ld lo = 0;
    ld hi = 1e9;

    for (int iter = 0; iter < 100; iter++) {
      const ld mid = (lo + hi) / 2;
      if (get_area_below(mid) < total / 2) {
        lo = mid;
      } else {
        hi = mid;
      }
    }

    return lo;
  }
};
