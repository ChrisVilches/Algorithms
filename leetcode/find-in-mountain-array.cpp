#include <bits/stdc++.h>
using namespace std;

class MountainArray {
 public:
  int get(int index);
  int length();
};

class Solution {
  int find_peak(MountainArray& arr) {
    const int n = arr.length();
    int lo = 1;
    int hi = n - 1;

    while (lo <= hi) {
      const int mid = (lo + hi) / 2;
      if (arr.get(mid) < arr.get(mid + 1)) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return lo;
  }

  int find_value(MountainArray& arr, const bool asc, const int from, const int to,
                 const int target) {
    int lo = from;
    int hi = to;

    while (lo <= hi) {
      const int mid = (lo + hi) / 2;
      const int value = arr.get(mid);
      if (value == target) return mid;

      const bool idx_too_low = (asc && value < target) || (!asc && value > target);

      if (idx_too_low) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return -1;
  }

 public:
  int findInMountainArray(const int target, MountainArray& mountainArr) {
    const int n = mountainArr.length();
    const int peak = find_peak(mountainArr);

    const int idx1 = find_value(mountainArr, true, 0, peak, target);
    const int idx2 = find_value(mountainArr, false, peak, n - 1, target);

    if (idx1 != -1) return idx1;
    return idx2;
  }
};
