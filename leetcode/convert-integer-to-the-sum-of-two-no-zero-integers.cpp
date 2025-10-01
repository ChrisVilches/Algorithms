#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool ok(int n) const {
    while (n > 0) {
      if (n % 10 == 0) return false;
      n /= 10;
    }

    return true;
  }

 public:
  vector<int> getNoZeroIntegers(const int n) {
    for (int a = 1; a < n; a++) {
      const int b = n - a;

      if (ok(a) && ok(b)) {
        return {a, b};
      }
    }

    assert(false);
  }
};
