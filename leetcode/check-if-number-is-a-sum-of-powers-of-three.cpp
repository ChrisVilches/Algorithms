#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool checkPowersOfThree(int number) {
    while (number > 0) {
      if (number % 3 > 1) return false;
      number /= 3;
    }

    return true;
  }
};
