#include <bits/stdc++.h>
using namespace std;

class Solution {
  int find_aux(const int idx, const vector<int>& nums, const vector<int>& other) {
    for (int lo = 0, hi = nums.size(); lo < hi;) {
      const int mid = (lo + hi) / 2;
      const int val = nums[mid];
      const int lower = lower_bound(other.begin(), other.end(), val) - other.begin();
      const int upper = upper_bound(other.begin(), other.end(), val) - other.begin();

      if (mid + lower <= idx && idx <= mid + upper) {
        return mid;
      }

      if (mid + lower < idx) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return -1;
  }

  int find(const int idx, const vector<int>& nums1, const vector<int>& nums2) {
    const int found_idx = find_aux(idx, nums1, nums2);
    if (found_idx != -1) return nums1[found_idx];

    return find(idx, nums2, nums1);
  }

 public:
  double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2) {
    const int total_length = nums1.size() + nums2.size();
    const int mid = total_length / 2;
    double result = find(mid, nums1, nums2);

    if (total_length % 2 == 0) {
      result += find(mid - 1, nums1, nums2);
      result /= 2;
    }

    return result;
  }
};
