#include <bits/stdc++.h>
using namespace std;

vector<int> compute_lps(const string& s) {
  const int n = s.size();
  vector<int> lps(n);
  lps.front() = 0;

  for (int i = 1, len = 0; i < n; i++) {
    while (len != 0 && s[i] != s[len]) len = lps[len - 1];
    if (s[i] == s[len]) len++;
    lps[i] = len;
  }
  return lps;
}

vector<int> kmp(const string& text, const string& pattern) {
  const int M = pattern.size();
  const int N = text.size();
  const vector<int> lps = compute_lps(pattern);
  vector<int> matches;

  for (int i = 0, j = 0; i < N;) {
    if (pattern[j] == text[i]) {
      j++;
      i++;
    }

    if (j == M) {
      matches.push_back(i - M);
      j = lps.back();
    } else if (i < N && pattern[j] != text[i]) {
      if (j != 0)
        j = lps[j - 1];
      else
        i++;
    }
  }

  return matches;
}

class Solution {
 public:
  int repeatedStringMatch(const string a, const string b) {
    const size_t min_size = a.size() + b.size();

    string longer = a;

    while (longer.size() < min_size) {
      longer += a;
    }

    const vector<int> matches = kmp(longer, b);

    if (matches.empty()) return -1;

    return (matches.front() + b.size() + a.size() - 1) / a.size();
  }
};
