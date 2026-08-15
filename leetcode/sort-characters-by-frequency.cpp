#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string frequencySort(string s) {
    unordered_map<char, int> freq;
    for (const char c : s) freq[c]++;

    sort(s.begin(), s.end(), [&](const char a, const char b) {
      return freq[a] > freq[b] || (freq[a] == freq[b] && a < b);
    });

    return s;
  }
};
