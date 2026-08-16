#include <bits/stdc++.h>
using namespace std;

class Solution {
  const string vowels = "aeiouAEIOU";

  bool is_vowel(const char c) const { return vowels.find(c) != vowels.npos; }

 public:
  string sortVowels(string s) {
    vector<char> v;

    for (const char c : s) {
      if (is_vowel(c)) v.emplace_back(c);
    }

    sort(v.begin(), v.end());

    int i = 0;

    for (char& c : s) {
      if (is_vowel(c)) c = v[i++];
    }

    return s;
  }
};
