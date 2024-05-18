#include <bits/stdc++.h>
using namespace std;

class Solution {
  int count(int x) {
    if (x == 0) return 0;
    const int val = x % 2;
    return val + count(x / 2);
  }

 public:
  vector<int> countBits(int n) {
    vector<int> result(n + 1);

    for (int i = 0; i < n + 1; i++) {
      result[i] = count(i);
    }

    return result;
  }
};
