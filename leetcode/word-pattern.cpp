#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool wordPattern(const string pattern, const string s) {
    vector<string> words;
    stringstream ss(s);
    string word;
    while (ss >> word) words.emplace_back(word);
    if (words.size() != pattern.size()) return false;

    unordered_map<char, string> m;
    unordered_map<string, char> inv;

    for (size_t i = 0; i < pattern.size(); i++) {
      const char c = pattern[i];

      if (m.count(c) && m[c] != words[i]) return false;
      if (inv.count(words[i]) && inv[words[i]] != c) return false;

      m[c] = words[i];
      inv[words[i]] = c;
    }

    return true;
  }
};
