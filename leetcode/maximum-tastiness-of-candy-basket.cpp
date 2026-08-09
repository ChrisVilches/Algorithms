#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximumTastiness(vector<int>& price, const int k) {
    sort(price.begin(), price.end());

    int lo = 0;
    int hi = price.back();

    while (lo <= hi) {
      const int mid = (lo + hi) / 2;

      int K = k - 1;
      int prev = price.front();

      for (const int p : price) {
        if (p - prev >= mid) {
          prev = p;
          K--;
        }
      }

      if (K <= 0) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return hi;
  }
};
