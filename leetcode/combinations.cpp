#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<vector<int>> ans;
  vector<int> curr;

  void choose(const int i, const int n, const int k) {
    if (k == 0) {
      ans.emplace_back(curr);
      return;
    }

    for (int j = i + 1; j <= n; j++) {
      curr.emplace_back(j);
      choose(j, n, k - 1);
      curr.pop_back();
    }
  }

 public:
  vector<vector<int>> combine(const int n, const int k) {
    for (int i = 1; i <= n; i++) {
      curr.emplace_back(i);
      choose(i, n, k - 1);
      curr.pop_back();
    }

    return ans;
  }
};
