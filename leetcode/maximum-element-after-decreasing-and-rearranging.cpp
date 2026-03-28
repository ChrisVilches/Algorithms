#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
    sort(arr.begin(), arr.end());

    int curr = 0;

    for (const int x : arr) {
      curr = min(x, curr + 1);
    }

    return curr;
  }
};
