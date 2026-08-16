#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int wateringPlants(const vector<int>& plants, const int capacity) {
    int ans = 0;
    int curr = capacity;

    for (size_t i = 0; i < plants.size(); i++) {
      if (plants[i] > curr) {
        curr = capacity;
        ans += i * 2;
      }

      ans++;
      curr -= plants[i];
    }

    return ans;
  }
};
