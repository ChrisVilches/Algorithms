#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;

 public:
  int maximumCandies(const vector<int>& candies, const ll k) {
    ll lo = 1;
    ll hi = 1e12 + 7;

    while (lo <= hi) {
      const ll mid = (lo + hi) / 2;

      ll alloc = 0;

      for (const ll c : candies) {
        alloc += c / mid;
      }

      if (alloc >= k) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return hi;
  }
};
