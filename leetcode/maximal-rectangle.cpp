#include <bits/stdc++.h>
using namespace std;

class Solution {
  int largest_rectangle_in_histogram(const vector<int>& heights) {
    const int n = heights.size();
    stack<int> s;
    int res = 0;

    for (int i = 0; i <= n; i++) {
      const int h = (i == n) ? 0 : heights[i];

      while (!s.empty() && heights[s.top()] > h) {
        const int height = heights[s.top()];
        s.pop();
        const int width = s.empty() ? i : i - s.top() - 1;
        res = max(res, height * width);
      }

      s.emplace(i);
    }

    return res;
  }

 public:
  int maximalRectangle(const vector<vector<char>>& matrix) {
    const int n = matrix.size();
    const int m = matrix.front().size();
    vector<int> heights(m, 0);
    int ans = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
      }

      ans = max(ans, largest_rectangle_in_histogram(heights));
    }

    return ans;
  }
};
