#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool rect_contains_origin(const int x1, const int y1, const int x2, const int y2) {
    return x1 <= 0 && 0 <= x2 && y1 <= 0 && 0 <= y2;
  }

  bool circle_contains_origin(const int x, const int y, const int r) {
    return (x * x) + (y * y) <= r * r;
  }

 public:
  bool checkOverlap(const int rad, const int x_center, const int y_center, int x1, int y1,
                    int x2, int y2) {
    x1 -= x_center;
    x2 -= x_center;
    y1 -= y_center;
    y2 -= y_center;

    if (circle_contains_origin(x1, y1, rad)) return true;
    if (circle_contains_origin(x1, y2, rad)) return true;
    if (circle_contains_origin(x2, y1, rad)) return true;
    if (circle_contains_origin(x2, y2, rad)) return true;

    if (rect_contains_origin(x1, y1, x2, y2)) return true;

    if (rect_contains_origin(x1 - rad, y1, x1 + rad, y2)) return true;
    if (rect_contains_origin(x2 - rad, y1, x2 + rad, y2)) return true;
    if (rect_contains_origin(x1, y1 - rad, x2, y1 + rad)) return true;
    if (rect_contains_origin(x1, y2 - rad, x2, y2 + rad)) return true;

    return false;
  }
};
