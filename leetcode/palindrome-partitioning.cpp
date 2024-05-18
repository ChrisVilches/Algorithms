#include <bits/stdc++.h>
using namespace std;

class Solution {
  string s;
  int n;
  vector<vector<string>> ans;
  vector<string> curr;

  bool is_palindrome(const string& s) {
    string r = s;
    reverse(r.begin(), r.end());
    return s == r;
  }

  void partition(const int i, const int j) {
    const string part = s.substr(i, j - i + 1);

    if (!is_palindrome(part)) {
      return;
    }

    curr.emplace_back(part);

    if (j == n - 1) {
      ans.push_back(curr);
    } else {
      for (int k = j + 1; k < n; k++) {
        partition(j + 1, k);
      }
    }

    curr.pop_back();
  }

 public:
  vector<vector<string>> partition(string s) {
    this->s = s;
    this->n = s.size();

    for (int i = 0; i < n; i++) {
      partition(0, i);
    }

    return ans;
  }
};
