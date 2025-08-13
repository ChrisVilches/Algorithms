#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numOfUnplacedFruits(const vector<int>& fruits, vector<int>& baskets) {
    int ok = 0;

    for (const int f : fruits) {
      for (int& b : baskets) {
        if (b >= f) {
          ok++;
          b = 0;
          break;
        }
      }
    }

    return fruits.size() - ok;
  }
};
