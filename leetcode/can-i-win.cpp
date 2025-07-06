#include <bits/stdc++.h>
using namespace std;

class Solution {
  unordered_map<int, bool> memo;
  int max_integer;

  bool dp(const int bitmask, const int desired) {
    const int memo_hash = bitmask + (desired << 22);

    if (memo.count(memo_hash)) {
      return memo[memo_hash];
    }

    for (int i = 0; i < max_integer; i++) {
      if ((bitmask & (1 << i)) != 0) continue;

      const int new_desired = desired - i - 1;

      if (new_desired <= 0 || !dp(bitmask | (1 << i), new_desired)) {
        return memo[memo_hash] = true;
      }
    }

    return memo[memo_hash] = false;
  }

 public:
  bool canIWin(const int maxChoosableInteger, const int desiredTotal) {
    max_integer = maxChoosableInteger;

    if (max_integer >= desiredTotal) return true;

    int sum = 0;

    for (int i = 1; i <= max_integer; i++) {
      sum += i;
    }

    return sum >= desiredTotal && dp(0, desiredTotal);
  }
};
