#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findCircleNum(vector<vector<int>>& isConnected) {
    const int n = isConnected.size();

    vector<bool> visited(n, false);

    int ans = 0;

    for (int i = 0; i < n; i++) {
      if (visited[i]) continue;

      ans++;
      queue<int> q;
      q.emplace(i);
      while (!q.empty()) {
        const int i = q.front();
        q.pop();
        visited[i] = true;

        for (int j = 0; j < n; j++) {
          if (!isConnected[i][j] || visited[j]) continue;

          visited[j] = true;
          q.emplace(j);
        }
      }
    }

    return ans;
  }
};
