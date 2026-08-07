#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  double angleClock(const int hour, const int minutes) {
    const double h = (hour % 12 + minutes / 60.0) * 30;

    const double angle = fabs(minutes * 6 - h);

    return min(angle, 360 - angle);
  }
};
