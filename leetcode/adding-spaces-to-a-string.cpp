#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string addSpaces(const string s, const vector<int>& spaces) {
    const int n = s.size();
    string res;

    for (int i = 0, j = 0; i < n; i++) {
      if (j < (int)spaces.size() && i == spaces[j]) {
        res += ' ';
        j++;
      }

      res += s[i];
    }

    return res;
  }
};
