#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> groupThePeople(const vector<int>& sizes) {
    unordered_map<int, vector<int>> groups;

    for (size_t i = 0; i < sizes.size(); i++) {
      const int size = sizes[i];
      groups[size].emplace_back(i);
    }

    vector<vector<int>> ans;

    for (const auto& [size, people] : groups) {
      for (size_t i = 0; i < people.size(); i++) {
        if (i % size == 0) ans.push_back({});
        ans.back().emplace_back(people[i]);
      }
    }

    return ans;
  }
};
