#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool canConstruct(const string ransomNote, const string magazine) {
    unordered_map<char, int> freq1, freq2;

    for (const char c : ransomNote) freq1[c]++;
    for (const char c : magazine) freq2[c]++;

    for (const auto& [letter, count] : freq1) {
      if (freq2[letter] < count) return false;
    }

    return true;
  }
};
