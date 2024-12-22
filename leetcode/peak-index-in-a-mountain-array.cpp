#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int peakIndexInMountainArray(const vector<int>& arr) {
    const int n = arr.size();
    int lo = 1;
    int hi = n - 2;

    while (lo < hi) {
      const int mid = (lo + hi) / 2;
      if (arr[mid] < arr[mid + 1]) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return lo;
  }
};
