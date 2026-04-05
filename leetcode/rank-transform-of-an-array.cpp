#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> arrayRankTransform(const vector<int>& arr) {
    vector<int> ans;
    ans.reserve(arr.size());

    vector<int> ord = arr;
    sort(ord.begin(), ord.end());

    unordered_map<int, int> rank;

    for (const int x : ord) {
      if (rank.count(x)) continue;
      rank[x] = rank.size() + 1;
    }

    for (const int x : arr) {
      ans.emplace_back(rank[x]);
    }

    return ans;
  }
};
