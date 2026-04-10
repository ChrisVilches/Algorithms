#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> sortByBits(vector<int>& arr) {
    sort(arr.begin(), arr.end(), [](const int a, const int b) {
      const int x = __builtin_popcount(a);
      const int y = __builtin_popcount(b);
      return x < y || (x == y && a < b);
    });
    return arr;
  }
};
