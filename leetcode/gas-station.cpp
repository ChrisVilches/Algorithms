#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    const int n = gas.size();

    multiset<int> curr;

    int left = 0;
    int right = 0;

    for (int i = 0; i < n; i++) {
      right += gas[i] - cost[i];
      curr.emplace(right);
    }

    for (int i = 0; i < n; i++) {
      if (*curr.begin() - left >= 0) return i;

      left += gas[i] - cost[i];
      right += gas[(i + n) % n] - cost[(i + n) % n];

      curr.emplace(right);
      curr.erase(curr.find(left));
    }

    return -1;
  }
};
