#include <bits/stdc++.h>
using namespace std;

struct Robot {
  int pos, health, dir, idx;
  bool right() const { return dir == 1; }
};

class Solution {
 public:
  vector<int> survivedRobotsHealths(const vector<int>& positions,
                                    const vector<int>& healths, const string directions) {
    vector<Robot> robots;

    for (size_t i = 0; i < positions.size(); i++) {
      robots.emplace_back(positions[i], healths[i], directions[i] == 'R', i);
    }

    sort(robots.begin(), robots.end(),
         [](const auto& a, const auto& b) { return a.pos < b.pos; });

    vector<Robot> s;

    for (Robot r : robots) {
      bool left_destroyed = false;

      if (!r.right()) {
        while (!left_destroyed && !s.empty() && s.back().right()) {
          if (s.back().health == r.health) {
            s.pop_back();
            left_destroyed = true;
          } else if (s.back().health > r.health) {
            s.back().health--;
            left_destroyed = true;
          } else {
            s.pop_back();
            r.health--;
          }
        }
      }

      if (!left_destroyed || r.right()) {
        s.emplace_back(r);
      }
    }

    sort(s.begin(), s.end(), [](const auto& a, const auto& b) { return a.idx < b.idx; });

    vector<int> ans;

    for (const Robot& r : s) {
      ans.emplace_back(r.health);
    }

    return ans;
  }
};
