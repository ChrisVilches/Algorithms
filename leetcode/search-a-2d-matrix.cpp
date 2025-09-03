#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool searchMatrix(const vector<vector<int>>& matrix, const int target) {
    int lo = 0;
    int hi = matrix.size() - 1;

    while (lo <= hi) {
      const int mid = (lo + hi) / 2;
      const vector<int>& row = matrix[mid];

      if (target < row.front()) {
        hi = mid - 1;
      } else if (row.back() < target) {
        lo = mid + 1;
      } else {
        return binary_search(row.begin(), row.end(), target);
      }
    }

    return false;
  }
};
