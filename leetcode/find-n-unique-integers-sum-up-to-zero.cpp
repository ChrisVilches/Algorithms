#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> sumZero(int n) {
    vector<int> ans;

    if (n % 2 == 1) {
      ans.emplace_back(0);
      n--;
    }

    n /= 2;

    for (int i = 1; i <= n; i++) {
      ans.emplace_back(i);
      ans.emplace_back(-i);
    }

    return ans;
  }
};
