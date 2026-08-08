#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findClosest(const int x, const int y, const int z) {
    const int dx = abs(x - z);
    const int dy = abs(y - z);

    if (dx == dy) return 0;

    return dx < dy ? 1 : 2;
  }
};
