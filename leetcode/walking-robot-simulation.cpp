#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
#define x first
#define y second

class Solution {
 public:
  int robotSim(const vector<int>& commands, const vector<vector<int>>& obstacles) {
    set<pii> obs;

    for (const auto& o : obstacles) {
      obs.emplace(o.front(), o.back());
    }

    int ans = 0;

    pii curr{0, 0}, dir{0, 1};

    for (const int cmd : commands) {
      switch (cmd) {
        case -2:
          dir = {-dir.y, dir.x};
          break;
        case -1:
          dir = {dir.y, -dir.x};
          break;
        default:
          for (int k = 0; k < cmd; k++) {
            const pii new_pos = {curr.x + dir.x, curr.y + dir.y};
            if (obs.count(new_pos)) break;
            curr = new_pos;
          }
          break;
      }

      ans = max(ans, curr.x * curr.x + curr.y * curr.y);
    }

    return ans;
  }
};
