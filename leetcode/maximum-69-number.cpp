#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximum69Number(const int num) {
    string digits = to_string(num);

    const auto it = find(digits.begin(), digits.end(), '6');

    if (it != digits.end()) {
      *it = '9';
    }

    return stoi(digits);
  }
};
