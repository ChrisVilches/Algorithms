#include <bits/stdc++.h>
using namespace std;

struct Robot {
  int pos, dist;
  bool operator<(const Robot r) const { return pos < r.pos; }
};

class Solution {
  static constexpr int max_n = 100'007;
  array<int, max_n> left{}, right{}, last_right{}, left_less{};
  vector<Robot> robots;

 public:
  int maxWalls(const vector<int>& robot_pos, const vector<int>& distance,
               vector<int>& walls) {
    const unordered_set<int> all_robot_pos{robot_pos.begin(), robot_pos.end()};

    for (size_t i = 0; i < robot_pos.size(); i++) {
      robots.emplace_back(robot_pos[i], distance[i]);
    }

    sort(walls.begin(), walls.end());
    sort(robots.begin(), robots.end());

    const int r = robots.size(), w = walls.size();
    int walls_same_pos_as_robot = 0;

    for (int i = 0, j = 0; i < w; i++) {
      if (all_robot_pos.count(walls[i])) {
        walls_same_pos_as_robot++;
        continue;
      }

      while (j < r - 1 && robots[j + 1].pos < walls[i]) j++;
      if (walls[i] < robots[j].pos) continue;
      if (walls[i] <= robots[j].pos + robots[j].dist) {
        right[j]++;
        last_right[j] = walls[i];
      }
    }

    for (int i = 0, j = 0; i < w; i++) {
      if (all_robot_pos.count(walls[i])) continue;

      while (j < r && robots[j].pos < walls[i]) j++;
      if (j == r) break;

      if (robots[j].pos - robots[j].dist <= walls[i]) {
        left[j]++;
        left_less[j] += j > 0 && last_right[j - 1] < walls[i];
      }
    }

    pair<int, int> curr, next{0, 0};

    for (int i = r - 1; i >= 0; i--) {
      const int right_val = right[i] + next.second;

      curr.first = max(left[i] + next.first, right_val);
      curr.second = max(left_less[i] + next.first, right_val);
      swap(curr, next);
    }

    return next.first + walls_same_pos_as_robot;
  }
};
