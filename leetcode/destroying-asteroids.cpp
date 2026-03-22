#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool asteroidsDestroyed(const int mass, vector<int>& asteroids) {
    long long curr = mass;

    sort(asteroids.begin(), asteroids.end());

    for (const long long x : asteroids) {
      if (x > curr) return false;
      curr += x;
    }

    return true;
  }
};
