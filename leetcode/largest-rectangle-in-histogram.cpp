#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    const int n = heights.size();

    vector<int> L(n), R(n);

    L[0] = -1;
    for (int i = 1; i < n; i++) {
      L[i] = i - 1;
      while (L[i] != -1 && heights[L[i]] >= heights[i]) L[i] = L[L[i]];
    }

    R[n - 1] = n;
    for (int i = n - 2; i >= 0; i--) {
      R[i] = i + 1;
      while (R[i] != n && heights[i] <= heights[R[i]]) R[i] = R[R[i]];
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
      const int width = R[i] - L[i] - 1;

      ans = max(ans, heights[i] * width);
    }

    return ans;
  }
};
