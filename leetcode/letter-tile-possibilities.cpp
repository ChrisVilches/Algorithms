#include <bits/stdc++.h>
using namespace std;

class Solution {
  set<string> ans;
  string curr;
  bool visited[10];
  string tiles;

  void recur(const int idx) {
    visited[idx] = true;
    curr += tiles[idx];
    ans.emplace(curr);

    for (size_t i = 0; i < tiles.size(); i++) {
      if (visited[i]) continue;
      recur(i);
    }

    curr.pop_back();
    visited[idx] = false;
  }

 public:
  int numTilePossibilities(const string input) {
    this->tiles = input;
    memset(visited, false, sizeof visited);

    for (size_t i = 0; i < tiles.size(); i++) {
      recur(i);
    }

    return ans.size();
  }
};
