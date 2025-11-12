#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isOneBitCharacter(const vector<int>& bits) {
    for (size_t i = 0; i < bits.size(); i++) {
      if (i == bits.size() - 1) return true;
      if (bits[i] == 1) i++;
    }

    return false;
  }
};
