#include <bits/stdc++.h>
using namespace std;

struct Circle {
  double x, y, r;
  bool contains(const double x0, const double y0) const {
    return pow(x - x0, 2) + pow(y - y0, 2) <= r * r;
  }
};

class Solution {
 public:
  int countLatticePoints(vector<vector<int>>& circles) {
    vector<Circle> cs;
    for (const vector<int>& c : circles) {
      cs.emplace_back(c[0], c[1], c[2]);
    }

    int ans = 0;

    for (int x = 0; x <= 200; x++) {
      for (int y = 0; y <= 200; y++) {
        for (const Circle& c : cs) {
          if (c.contains(x, y)) {
            ans++;
            break;
          }
        }
      }
    }

    return ans;
  }
};
