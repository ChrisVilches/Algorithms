#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int monotoneIncreasingDigits(const int num) {
    vector<int> digits;

    if (num == 0) return 0;

    for (int x = num; x > 0; x /= 10) {
      digits.emplace_back(x % 10);
    }

    const int n = digits.size();

    while (true) {
      int i = 0;

      for (; i < n - 1; i++) {
        if (digits[i] < digits[i + 1]) break;
      }

      if (i == n - 1) break;

      i++;

      fill(digits.begin(), digits.begin() + i, 9);

      while (i < n) {
        digits[i]--;
        if (digits[i] != -1) break;
        digits[i] = 9;
        i++;
      }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
      ans += digits[i] * pow(10, i);
    }

    return ans;
  }
};
