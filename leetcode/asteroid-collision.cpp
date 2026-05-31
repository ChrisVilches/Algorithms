#include <bits/stdc++.h>
using namespace std;

class Solution {
  void add_left(vector<int>& s, const int x) const {
    while (!s.empty() && s.back() > 0) {
      const int prev = s.back();
      if (prev <= x) s.pop_back();
      if (prev >= x) return;
    }

    s.emplace_back(-x);
  }

 public:
  vector<int> asteroidCollision(const vector<int>& asteroids) {
    vector<int> s;

    for (const int x : asteroids) {
      if (x > 0) {
        s.emplace_back(x);
      } else {
        add_left(s, abs(x));
      }
    }

    return s;
  }
};
