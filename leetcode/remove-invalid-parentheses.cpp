#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool valid(const string& s) {
    int curr = 0;
    for (const char c : s) {
      if (c == '(') {
        curr++;
      } else if (c == ')') {
        curr--;
      }
      if (curr == -1) return false;
    }
    return curr == 0;
  }

 public:
  vector<string> removeInvalidParentheses(const string s) {
    queue<string> q;
    unordered_set<string> visited;

    vector<string> ans;

    q.emplace(s);
    visited.emplace(s);

    int str_length = 0;

    while (!q.empty()) {
      const string curr = q.front();
      q.pop();

      const bool is_valid = valid(curr);

      if (ans.empty() && is_valid) {
        str_length = curr.size();
      }

      if (is_valid) {
        ans.emplace_back(curr);
        continue;
      }

      if (curr.size() < str_length) continue;

      for (int i = 0; i < (int)curr.size(); i++) {
        if (curr[i] != '(' && curr[i] != ')') continue;
        string next_str = curr;
        next_str.erase(next_str.begin() + i);
        if (visited.count(next_str)) continue;
        visited.emplace(next_str);
        q.emplace(next_str);
      }
    }

    return ans;
  }
};
