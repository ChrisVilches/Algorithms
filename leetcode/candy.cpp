#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int candy(const vector<int>& ratings) {
    const int n = ratings.size();
    if (n == 1) return 1;

    vector<int> valleys;

    for (int i = 0; i < n; i++) {
      const bool left = i == 0 || ratings[i - 1] >= ratings[i];
      const bool right = i == n - 1 || ratings[i] <= ratings[i + 1];

      if (left && right) valleys.emplace_back(i);
    }

    vector<int> res(n, 0);

    for (const int v_idx : valleys) {
      res[v_idx] = 1;

      for (int i = v_idx - 1; i >= 0; i--) {
        if (ratings[i] <= ratings[i + 1]) break;

        res[i] = max(res[i], res[i + 1] + 1);
      }

      for (int i = v_idx + 1; i < n; i++) {
        if (ratings[i - 1] >= ratings[i]) break;

        res[i] = max(res[i], res[i - 1] + 1);
      }
    }

    return accumulate(res.begin(), res.end(), 0);
  }
};
