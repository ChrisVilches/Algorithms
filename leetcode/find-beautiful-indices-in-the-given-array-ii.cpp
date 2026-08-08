#include <bits/stdc++.h>
using namespace std;

vector<int> kmp(const string& text, const string& pattern) {
  vector<int> lps(pattern.size());
  lps.front() = 0;
  for (size_t i = 1, len = 0; i < pattern.size(); i++) {
    while (len != 0 && pattern[i] != pattern[len]) len = lps[len - 1];
    if (pattern[i] == pattern[len]) len++;
    lps[i] = len;
  }
  vector<int> matches;
  for (size_t i = 0, j = 0; i < text.size(); i++) {
    while (j != 0 && text[i] != pattern[j]) j = lps[j - 1];
    if (text[i] == pattern[j]) j++;
    if (j == pattern.size()) {
      matches.emplace_back(i - j + 1);
      j = lps[j - 1];
    }
  }
  return matches;
}

class Solution {
 public:
  vector<int> beautifulIndices(const string s, const string a, const string b,
                               const int k) {
    const vector<int> idx_a = kmp(s, a);
    const vector<int> idx_b = kmp(s, b);

    vector<int> ans;
    size_t j = 0;

    for (const int i : idx_a) {
      while (j < idx_b.size() && idx_b[j] < i - k) j++;

      if (j < idx_b.size() && abs(idx_b[j] - i) <= k) {
        ans.emplace_back(i);
      }
    }

    return ans;
  }
};
