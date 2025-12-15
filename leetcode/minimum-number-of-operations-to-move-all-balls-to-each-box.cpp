#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> minOperations(const string boxes) {
    const int n = boxes.size();
    vector<int> ans;

    for (int i = 0; i < n; i++) {
      ans.emplace_back(0);

      for (int j = 0; j < n; j++) {
        if (boxes[j] == '1') {
          ans.back() += abs(j - i);
        }
      }
    }

    return ans;
  }
};
