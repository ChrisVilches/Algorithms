#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<long long> sumOfThree(long long num) {
    num -= 3;
    if (num % 3 != 0) return vector<long long>();

    const long long x = num / 3;

    return {x, x + 1, x + 2};
  }
};
