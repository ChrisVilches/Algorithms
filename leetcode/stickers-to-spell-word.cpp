#include <bits/stdc++.h>
using namespace std;

class Solution {
  int target_n;
  vector<string> stickers;
  unordered_map<char, vector<int>> char_idx;
  const int inf = 1e5;
  int memo[(1 << 15) + 7][57];

  int dp(const int bitmask, const size_t idx) {
    if (bitmask == (1 << target_n) - 1) return 0;
    if (idx == stickers.size()) return inf;
    if (~memo[bitmask][idx]) return memo[bitmask][idx];

    int new_bitmask = bitmask;
    int res = dp(bitmask, idx + 1);
    bool ok = true;

    for (int times = 1; times <= target_n && ok; times++) {
      ok = false;
      for (const char c : stickers[idx]) {
        for (const int i : char_idx[c]) {
          if ((new_bitmask & (1 << i)) != 0) continue;

          new_bitmask |= 1 << i;
          ok = true;
          break;
        }
      }

      res = min(res, times + dp(new_bitmask, idx + 1));
    }

    return memo[bitmask][idx] = res;
  }

 public:
  int minStickers(const vector<string>& stickers_input, const string target) {
    this->stickers = stickers_input;
    this->target_n = target.size();
    for (int i = 0; i < target_n; i++) char_idx[target[i]].emplace_back(i);

    memset(memo, -1, sizeof memo);

    const int res = dp(0, 0);
    return res == inf ? -1 : res;
  }
};
