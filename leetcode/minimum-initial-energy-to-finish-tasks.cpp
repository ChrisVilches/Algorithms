#include <bits/stdc++.h>
using namespace std;

#define actual front()
#define minimum back()

class Solution {
  bool possible(const vector<vector<int>>& tasks, const int initial) {
    int curr = initial;

    for (const auto& task : tasks) {
      if (curr < task.minimum) return false;
      curr -= task.actual;
    }

    return true;
  }

 public:
  int minimumEffort(vector<vector<int>>& tasks) {
    sort(tasks.begin(), tasks.end(), [](const auto& a, const auto& b) {
      return a.minimum - a.actual > b.minimum - b.actual;
    });

    int lo = 1;
    int hi = 1e9 + 7;

    while (lo <= hi) {
      const int mid = lo + (hi - lo) / 2;

      if (possible(tasks, mid)) {
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    }

    return lo;
  }
};
