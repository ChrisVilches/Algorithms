#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxDistance(vector<int>& position, const int m) {
    sort(position.begin(), position.end());

    int lo = 0;
    int hi = 2e9;

    while (lo < hi) {
      const int mid = (lo + hi) / 2;

      int rem = m;
      int prev = 0;

      for (const int p : position) {
        if (prev == 0 || p - prev >= mid) {
          rem--;
          prev = p;
        }
      }

      if (rem <= 0) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return lo - 1;
  }
};
