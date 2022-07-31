#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tiii;

struct Segtree {
 private:
  vector<int> tree;
  int n;
  inline int left(int p) { return p << 1; }
  inline int right(int p) { return (p << 1) + 1; }

  int min_query(int p, int L, int R, int i, int j) {
    if (i > R || j < L) return INT_MAX;
    if (L >= i && R <= j) return tree[p];
    return min(min_query(left(p), L, (L + R) / 2, i, j),
               min_query(right(p), (L + R) / 2 + 1, R, i, j));
  }

  void update(int p, int L, int R, int pos, int new_val) {
    if (L == R) {
      tree[p] = new_val;
    } else {
      int m = (L + R) / 2;
      if (pos <= m)
        update(left(p), L, m, pos, new_val);
      else
        update(right(p), m + 1, R, pos, new_val);
      tree[p] = min(tree[left(p)], tree[right(p)]);
    }
  }

 public:
  Segtree(int n) : n(n) { tree.assign(4 * n, 0); }
  int min_query(int i, int j) { return min_query(1, 0, n - 1, i, j); }
  void update(int pos, int val) { return update(1, 0, n - 1, pos, val); }
};

struct Point {
  int x, y;
  bool operator<(const Point& p) const { return y < p.y; }
};

int compress(vector<tiii>& sensors, vector<Point>& droplets) {
  vector<tuple<int, bool, bool, int>> all_x;

  for (int i = 0; i < (int)droplets.size(); i++) {
    all_x.emplace_back(droplets[i].x, false, false, i);
  }

  for (int i = 0; i < (int)sensors.size(); i++) {
    const auto [y, x1, x2] = sensors[i];
    all_x.emplace_back(x1, true, true, i);
    all_x.emplace_back(x2, true, false, i);
  }

  sort(all_x.begin(), all_x.end());

  int curr_x = 0;
  int original_x = get<0>(all_x.front());

  for (const auto& [x, sensor, first_endpoint, idx] : all_x) {
    if (x != original_x) {
      curr_x++;
      original_x = x;
    }

    if (!sensor) {
      droplets[idx].x = curr_x;
      continue;
    }

    if (first_endpoint) {
      get<1>(sensors[idx]) = curr_x;
    } else {
      get<2>(sensors[idx]) = curr_x;
    }
  }

  return curr_x;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int D, S;

  while (cin >> D >> S) {
    map<pair<int, int>, int> ans;

    vector<tiii> sensors(S);
    vector<Point> original_droplets(D);

    for (Point& d : original_droplets) cin >> d.x >> d.y;

    for (tiii& s : sensors) {
      int x1, x2, y;
      cin >> x1 >> x2 >> y;
      s = {y, x1, x2};
    }

    const int max_x = compress(sensors, original_droplets) + 1;

    priority_queue<Point> droplets{original_droplets.begin(), original_droplets.end()};

    sort(sensors.rbegin(), sensors.rend());

    Segtree segtree(max_x);

    for (int i = 0; i < max_x; i++) {
      segtree.update(i, INT_MAX);
    }

    map<int, set<int>> y_points;
    map<int, stack<int>> x_values;

    for (const auto& [y, x1, x2] : sensors) {
      while (!droplets.empty() && droplets.top().y >= y) {
        const Point d = droplets.top();
        y_points[d.y].insert(d.x);
        segtree.update(d.x, d.y);
        x_values[d.x].push(d.y);
        droplets.pop();
      }

      const int min_y = segtree.min_query(x1, x2);

      if (min_y == INT_MAX) continue;

      set<int>& points = y_points[min_y];

      while (true) {
        const auto it = points.lower_bound(x1);
        if (it == points.end()) break;
        const int x = *it;
        if (x2 < x) break;

        x_values[x].pop();

        const int new_value = x_values[x].empty() ? INT_MAX : x_values[x].top();

        segtree.update(x, new_value);

        ans[{x, min_y}] = y;
        points.erase(it);
      }
    }

    for (const Point& d : original_droplets) {
      cout << ans[{d.x, d.y}] << '\n';
    }
  }
}
