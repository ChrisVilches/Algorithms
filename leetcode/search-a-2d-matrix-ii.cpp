#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool searchMatrix(const vector<vector<int>>& matrix, const int target) {
    for (const vector<int>& row : matrix) {
      if (binary_search(row.begin(), row.end(), target)) {
        return true;
      }
    }

    return false;
  }
};
