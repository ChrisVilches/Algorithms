#include <bits/stdc++.h>
using namespace std;

class Solution {
  int overlap[13][13];
  vector<string> words;

  int find_overlap(const string& a, const string& b) {
    const int n = a.size();
    const int m = b.size();

    for (int i = max(n - m, 0); i < n; i++) {
      bool ok = true;
      for (int j = i, k = 0; j < n && k < m;) {
        if (a[j++] != b[k++]) {
          ok = false;
          break;
        }
      }
      if (ok) return n - i;
    }
    return 0;
  }

  map<pair<int, int>, pair<int, int>> memo;

  pair<int, int> dp(const int bitmask, const int idx) {
    const int n = words.size();
    if (bitmask == (1 << n) - 1) return {words[idx].size(), -1};

    if (memo.count({bitmask, idx})) return memo[{bitmask, idx}];

    pair<int, int> res{1e9, -1};

    for (int i = 0; i < n; i++) {
      if ((bitmask & (1 << i)) != 0) continue;
      const int word_len = words[idx].size() - overlap[idx][i];
      const int length = word_len + dp(bitmask | (1 << i), i).first;
      res = min(res, {length, i});
    }

    return memo[{bitmask, idx}] = res;
  }

 public:
  string shortestSuperstring(vector<string>& words) {
    memset(overlap, 0, sizeof overlap);
    this->words = words;
    const int n = words.size();

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        overlap[i][j] = find_overlap(words[i], words[j]);
      }
    }

    pair<int, int> min_elem{1e9, -1};

    for (int i = 0; i < n; i++) {
      min_elem = min(min_elem, {dp(1 << i, i).first, i});
    }

    string ans = "";

    for (int i = min_elem.second, bitmask = 0; i != -1;) {
      int overlap = find_overlap(ans, words[i]);
      while (overlap--) ans.pop_back();

      ans += words[i];
      bitmask |= 1 << i;
      i = dp(bitmask, i).second;
    }

    return ans;
  }
};
