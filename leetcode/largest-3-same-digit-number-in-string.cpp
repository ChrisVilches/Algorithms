#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string largestGoodInteger(const string num) {
    int digit = -1;

    for (size_t i = 0; i < num.size() - 2; i++) {
      if (num[i] != num[i + 1] || num[i] != num[i + 2]) continue;
      digit = max(digit, num[i] - '0');
    }

    return digit == -1 ? "" : string(3, '0' + digit);
  }
};
