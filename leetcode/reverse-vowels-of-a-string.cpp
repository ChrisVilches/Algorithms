#include <bits/stdc++.h>
using namespace std;

class Solution {
  const string vowels = "aeiouAEIOU";

 public:
  string reverseVowels(string s) {
    stack<char> values;

    for (const char c : s) {
      if (vowels.find(c) != vowels.npos) {
        values.push(c);
      }
    }

    for (char& c : s) {
      if (vowels.find(c) != vowels.npos) {
        c = values.top();
        values.pop();
      }
    }

    return s;
  }
};
