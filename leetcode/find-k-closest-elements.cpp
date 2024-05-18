#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    stack<int> lo;
    queue<int> hi;
    for (const auto& val : arr) {
      if (val < x) {
        lo.push(val);
      } else {
        hi.push(val);
      }
    }

    multiset<int> res;

    while (k--) {
      const int a = lo.empty() ? 1e5 : lo.top();
      const int b = hi.empty() ? 1e5 : hi.front();

      if (abs(a - x) <= abs(b - x)) {
        res.emplace(a);
        lo.pop();
      } else {
        res.emplace(b);
        hi.pop();
      }
    }

    return {res.begin(), res.end()};
  }
};
