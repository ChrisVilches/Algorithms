#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxCoins(vector<int>& piles) {
    sort(piles.begin(), piles.end());

    int ans = 0;
    int iter = piles.size() / 3;

    while (iter--) {
      piles.pop_back();
      ans += piles.back();
      piles.pop_back();
    }

    return ans;
  }
};
