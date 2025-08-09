#include <bits/stdc++.h>
using namespace std;

class Solution {
  tuple<int, int, int> find_max_dist(const vector<vector<int>>& points) {
    array<int, 4> min_val, max_val;
    array<int, 4> min_idx, max_idx;

    fill(min_val.begin(), min_val.end(), INT_MAX);
    fill(max_val.begin(), max_val.end(), INT_MIN);
    fill(min_idx.begin(), min_idx.end(), -1);
    fill(max_idx.begin(), max_idx.end(), -1);

    for (size_t i = 0; i < points.size(); i++) {
      const int x = points[i][0];
      const int y = points[i][1];

      const array<int, 4> vals{x + y, x - y, -x + y, -x - y};

      for (int k = 0; k < 4; k++) {
        if (vals[k] < min_val[k]) {
          min_val[k] = vals[k];
          min_idx[k] = i;
        }
        if (vals[k] > max_val[k]) {
          max_val[k] = vals[k];
          max_idx[k] = i;
        }
      }
    }

    tuple<int, int, int> res{-1, -1, -1};

    for (int k = 0; k < 4; k++) {
      const int dist = max_val[k] - min_val[k];
      if (dist > get<2>(res)) {
        res = {max_idx[k], min_idx[k], dist};
      }
    }

    return res;
  }

 public:
  int minimumDistance(const vector<vector<int>>& points) {
    const auto [i, j, _] = find_max_dist(points);

    auto a = points;
    auto b = points;

    a.erase(a.begin() + i);
    b.erase(b.begin() + j);

    const int dist1 = get<2>(find_max_dist(a));
    const int dist2 = get<2>(find_max_dist(b));

    return min(dist1, dist2);
  }
};
