#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool checkStrings(const string s1, const string s2) {
    array<array<int, 26>, 2> counts1{}, counts2{};

    for (size_t i = 0; i < s1.size(); i++) {
      counts1[i % 2][s1[i] - 'a']++;
      counts2[i % 2][s2[i] - 'a']++;
    }

    return counts1 == counts2;
  }
};
