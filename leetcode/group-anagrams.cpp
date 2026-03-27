#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<string>> groupAnagrams(const vector<string>& strs) {
    map<string, vector<string>> groups;

    for (const string& s : strs) {
      string r = s;
      sort(r.begin(), r.end());
      groups[r].emplace_back(s);
    }

    vector<vector<string>> ans;

    for (const auto& [_, group] : groups) {
      ans.emplace_back(group);
    }

    return ans;
  }
};
