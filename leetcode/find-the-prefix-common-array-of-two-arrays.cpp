#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> findThePrefixCommonArray(const vector<int>& A, const vector<int>& B) {
    vector<int> ans;

    unordered_set<int> a_set;

    for (size_t i = 0; i < A.size(); i++) {
      a_set.emplace(A[i]);
      ans.emplace_back(0);

      for (size_t j = 0; j <= i; j++) {
        ans.back() += a_set.count(B[j]);
      }
    }

    return ans;
  }
};
