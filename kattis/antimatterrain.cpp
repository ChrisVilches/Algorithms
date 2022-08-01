#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tiii;

struct Segtree {
 private:
  vector<int> tree;
  const int n;

  int min_query(int p, int L, int R, int i, int j) {
    if (R < i || j < L) return INT_MAX;
    if (i <= L && R <= j) return tree[p];
    return min(min_query(2 * p, L, (L + R) / 2, i, j),
               min_query(2 * p + 1, (L + R) / 2 + 1, R, i, j));
  }

  void update(int p, int L, int R, int pos, int new_val) {
    if (L == R) {
      tree[p] = new_val;
    } else {
      const int m = (L + R) / 2;
      if (pos <= m)
        update(2 * p, L, m, pos, new_val);
      else
        update(2 * p + 1, m + 1, R, pos, new_val);
      tree[p] = min(tree[2 * p], tree[2 * p + 1]);
    }
  }

 public:
  Segtree(int n, int init = 0) : tree(vector<int>(4 * n, init)), n(n) {}
  int min_query(int i, int j) { return min_query(1, 0, n - 1, i, j); }
  void update(int pos, int val) { return update(1, 0, n - 1, pos, val); }
};

struct Point {
  int x, y;
  bool operator<(const Point& p) const { return y < p.y || (y == p.y && x < p.x); }
};

int compress(vector<tiii>& sensors, vector<Point>& droplets) {
  vector<tiii> all_x;

  for (int i = 0; i < (int)droplets.size(); i++) {
    all_x.emplace_back(droplets[i].x, 1, i);
  }

  for (int i = 0; i < (int)sensors.size(); i++) {
    const auto [_, x1, x2] = sensors[i];
    all_x.emplace_back(x1, 0, i);
    all_x.emplace_back(x2, 2, i);
  }

  sort(all_x.begin(), all_x.end());

  int curr_x = 0;

  for (const auto& [x, type, idx] : all_x) {
    switch (type) {
      case 0:
        get<1>(sensors[idx]) = curr_x;
        break;
      case 1:
        droplets[idx].x = curr_x;
        break;
      case 2:
        get<2>(sensors[idx]) = curr_x;
        break;
    }

    curr_x++;
  }

  return curr_x;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int D, S;

  while (cin >> D >> S) {
    vector<tiii> sensors(S);
    vector<Point> droplets(D);
    map<Point, int> point_idx;
    vector<int> ans(D, 0);
    unordered_map<int, set<int>> y_points;

    for (Point& d : droplets) cin >> d.x >> d.y;
    for (tiii& s : sensors) cin >> get<1>(s) >> get<2>(s) >> get<0>(s);

    const int max_x = compress(sensors, droplets) + 1;
    Segtree segtree(max_x, INT_MAX);

    for (int i = 0; i < D; i++) {
      point_idx[droplets[i]] = i;
      y_points[droplets[i].y].insert(droplets[i].x);
    }

    sort(droplets.rbegin(), droplets.rend());
    sort(sensors.rbegin(), sensors.rend());

    auto droplet_it = droplets.begin();

    for (const auto& [y, x1, x2] : sensors) {
      while (droplet_it != droplets.end() && droplet_it->y >= y) {
        segtree.update(droplet_it->x, droplet_it->y);
        ++droplet_it;
      }

      const int min_y = segtree.min_query(x1, x2);

      if (min_y == INT_MAX) continue;

      set<int>& points = y_points[min_y];

      while (true) {
        const auto it = points.lower_bound(x1);
        if (it == points.end()) break;
        const int x = *it;
        if (x2 < x) break;

        ans[point_idx[{x, min_y}]] = y;

        segtree.update(x, INT_MAX);
        points.erase(it);
      }
    }

    for (const int a : ans) {
      cout << a << '\n';
    }
  }
}
