#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int eatenApples(vector<int>& apples, vector<int>& days) {
    const int n = apples.size();

    int ans = 0;

    map<pair<int, int>, int> curr;

    map<int, vector<int>> remove;

    for (int i = 0; !curr.empty() || i < n; i++) {
      for (const int j : remove[i]) {
        curr.erase({j + days[j], j});
      }

      if (i < n && apples[i] != 0) {
        remove[i + days[i]].emplace_back(i);
        curr[{i + days[i], i}] = apples[i];
      }

      if (!curr.empty()) {
        const auto it = curr.begin();
        it->second--;
        ans++;
        if (it->second == 0) {
          curr.erase(it);
        }
      }
    }

    return ans;
  }
};
