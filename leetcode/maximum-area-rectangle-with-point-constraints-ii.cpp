#include <bits/stdc++.h>
using namespace std;
using Point = pair<int, int>;
#define x first
#define y second

class Solution {
  vector<int> tree;

  int max_query(const int p, const int l, const int r, const int i, const int j) {
    if (i > r || j < l) return -1;
    if (i <= l && r <= j) return tree[p];
    const int m = (l + r) / 2;
    return max(max_query(2 * p, l, m, i, j), max_query(2 * p + 1, m + 1, r, i, j));
  }

  void update(const int p, const int l, const int r, const int pos, const int val) {
    if (l == r) {
      tree[p] = val;
    } else {
      int m = (l + r) / 2;
      if (pos <= m)
        update(2 * p, l, m, pos, val);
      else
        update(2 * p + 1, m + 1, r, pos, val);
      tree[p] = max(tree[2 * p], tree[2 * p + 1]);
    }
  }

 public:
  long long maxRectangleArea(const vector<int>& xCoord, const vector<int>& yCoord) {
    vector<Point> points;

    for (int i = 0; i < (int)xCoord.size(); i++) {
      points.emplace_back(xCoord[i], yCoord[i]);
    }

    long long ans = -1;

    set<int> all_y;
    unordered_map<int, int> idx;
    for (const Point& p : points) all_y.emplace(p.y);
    for (const int y : all_y) idx[y] = idx.size();

    const int tree_n = idx.size();
    tree.assign(4 * tree_n, -1);

    map<int, set<int>> by_x;
    for (const Point& p : points) {
      by_x[p.x].emplace(p.y);
    }

    for (const auto& [x, ys] : by_x) {
      for (auto it = ys.begin(); it != ys.end(); it++) {
        if (next(it) == ys.end()) continue;

        const int y1 = *it;
        const int y2 = *next(it);

        const int x1 = max_query(1, 0, tree_n - 1, idx[y1], idx[y1]);
        const int x2 = max_query(1, 0, tree_n - 1, idx[y2], idx[y2]);

        if (x1 == -1) continue;
        if (x1 != x2) continue;

        const int i = idx[y1] + 1;
        const int j = idx[y2] - 1;

        if (i > j || max_query(1, 0, tree_n - 1, i, j) < x1) {
          const long long area = (long long)(y2 - y1) * (x - x1);
          ans = max(ans, area);
        }
      }

      for (const int y : ys) {
        update(1, 0, tree_n - 1, idx[y], x);
      }
    }

    return ans;
  }
};
