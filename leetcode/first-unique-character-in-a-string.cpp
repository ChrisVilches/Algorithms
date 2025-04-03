#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int firstUniqChar(const string s) {
    unordered_map<char, int> freq;
    for (const char c : s) freq[c]++;

    for (size_t i = 0; i < s.size(); i++) {
      if (freq[s[i]] == 1) return i;
    }

    return -1;
  }
};
