#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;

 public:
  bool isPathCrossing(const string path) {
    pair<ll, ll> curr{0, 0};
    unordered_set<ll> visited{0};
    for (const char c : path) {
      if (c == 'N') {
        curr.second++;
      } else if (c == 'E') {
        curr.first++;
      } else if (c == 'W') {
        curr.first--;
      } else if (c == 'S') {
        curr.second--;
      }

      const ll hash = (curr.first << 32) + curr.second;
      if (visited.count(hash)) return true;
      visited.emplace(hash);
    }

    return false;
  }
};
