#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool contains(const int a, const int b, const int x) { return a <= x && x <= b; };

  template <typename T>
  void insert_sorted(vector<T>& arr, T item) {
    arr.emplace_back(item);

    for (int i = arr.size() - 1; i >= 1; i--) {
      auto& a = arr[i - 1];
      auto& b = arr[i];

      if (a > b) {
        swap(a, b);
      } else {
        break;
      }
    }
  }

 public:
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> ans;

    int x = newInterval[0];
    int y = newInterval[1];

    for (const auto& interval : intervals) {
      const int a = interval[0];
      const int b = interval[1];
      if (contains(a, b, x)) x = min(x, a);
      if (contains(a, b, y)) y = max(y, b);
    }

    for (const auto& interval : intervals) {
      const int a = interval[0];
      const int b = interval[1];

      if (!contains(x, y, a) && !contains(x, y, b)) {
        ans.push_back({a, b});
      }
    }

    insert_sorted(ans, {x, y});
    return ans;
  }
};
