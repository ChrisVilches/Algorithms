#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool visited[1001][1001];

 public:
  bool canMeasureWater(const int x, const int y, const int target) {
    queue<pair<int, int>> q;
    memset(visited, 0, sizeof visited);

    const auto add = [&](const int a, const int b) {
      if (visited[a][b]) return;
      q.emplace(a, b);
      visited[a][b] = true;
    };

    add(0, 0);

    while (!q.empty()) {
      const auto [a, b] = q.front();
      q.pop();
      if (a + b == target) return true;

      add(a, 0);
      add(0, b);
      add(x, b);
      add(a, y);

      const int pour1 = min(x - a, b);
      add(a + pour1, b - pour1);

      const int pour2 = min(a, y - b);
      add(a - pour2, b + pour2);
    }

    return false;
  }
};
