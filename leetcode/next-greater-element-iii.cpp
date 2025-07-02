#include <bits/stdc++.h>
using namespace std;

class Solution {
  int try_convert(const vector<int>& digits) {
    long long ret = 0;

    for (size_t i = 0; i < digits.size(); i++) {
      ret += digits[i] * pow(10, i);
      if (ret > (1L << 31) - 1) return -1;
    }

    return ret;
  }

 public:
  int nextGreaterElement(int n) {
    vector<int> digits;

    while (n > 0) {
      digits.emplace_back(n % 10);
      n /= 10;
    }

    const int d = digits.size();

    map<int, int> m;

    for (int i = 0; i < d; i++) {
      const auto it = m.lower_bound(digits[i] + 1);
      if (it != m.end()) {
        const int idx = it->second;
        swap(digits[i], digits[idx]);
        sort(digits.begin(), digits.begin() + i, greater<int>());
        return try_convert(digits);
      }

      m[digits[i]] = i;
    }

    return -1;
  }
};
