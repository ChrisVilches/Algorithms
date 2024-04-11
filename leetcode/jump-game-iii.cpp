#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool canReach(vector<int>& arr, int start) {
    if (start < 0) return false;
    if (start >= (int)arr.size()) return false;
    if (arr[start] == -1) return false;
    if (arr[start] == 0) return true;

    const int val = arr[start];
    arr[start] = -1;
    return canReach(arr, start - val) || canReach(arr, start + val);
  }
};
