#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool kmp(const string& pattern, const string& text, const vector<int>& lps) const {
    for (size_t i = 0, j = 0; i < text.size(); i++) {
      while (j > 0 && pattern[j] != text[i]) j = lps[j - 1];
      if (pattern[j] == text[i]) j++;
      if (j == pattern.size()) return true;
    }
    return false;
  }

  bool is_substring(const vector<string>& words, const size_t idx) const {
    const string& s = words[idx];
    const int n = s.size();
    vector<int> lps(n);
    lps.front() = 0;
    for (int i = 1, len = 0; i < n; i++) {
      while (len != 0 && s[i] != s[len]) len = lps[len - 1];
      if (s[i] == s[len]) len++;
      lps[i] = len;
    }

    for (size_t i = 0; i < words.size(); i++) {
      if (i != idx && kmp(s, words[i], lps)) return true;
    }

    return false;
  }

 public:
  vector<string> stringMatching(const vector<string>& words) {
    vector<string> ans;

    for (size_t i = 0; i < words.size(); i++) {
      if (is_substring(words, i)) {
        ans.emplace_back(words[i]);
      }
    }

    return ans;
  }
};
