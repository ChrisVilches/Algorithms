#include <bits/stdc++.h>
using namespace std;

struct BIT {
  BIT(const int n) : A(n + 1, 0) {}

  void update(int i, const int v) {
    i++;
    for (; i < (int)A.size(); i += i & -i) A[i] += v;
  }

  int query(int i) {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

 private:
  vector<int> A;
};

struct Point {
  int x, y;
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  long long cross(const Point p) const { return (long long)x * p.y - (long long)y * p.x; }
  bool first_half() const { return y > 0 || (y == 0 && x > 0); }
  bool operator<(const Point p) const {
    return first_half() != p.first_half() ? first_half() : cross(p) > 0;
  }
};

vector<Point> read_points() {
  int n;
  cin >> n;
  vector<Point> res(n);
  for (Point& p : res) cin >> p.x >> p.y;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;

  while (cin >> n) {
    unordered_map<int, unordered_map<int, int>> ans;
    unordered_map<int, unordered_set<int>> from;
    vector<pair<int, int>> queries;
    vector<vector<Point>> polygons(n);

    for (auto& poly : polygons) poly = read_points();

    cin >> q;

    for (int i = 0; i < q; i++) {
      int l, r;
      cin >> l >> r;
      l--;
      r--;
      from[r].emplace(l);
      queries.emplace_back(l, r);
    }

    BIT bit(n);
    map<Point, int> prev_pos;

    for (int i = 0; i < n; i++) {
      const auto& P = polygons[i];

      for (int j = 0; j < (int)P.size(); j++) {
        const Point edge = P[(j + 1) % P.size()] - P[j];
        if (prev_pos.count(edge)) {
          bit.update(prev_pos[edge], -1);
        }
        bit.update(i, 1);
        prev_pos[edge] = i;
      }

      for (const int left : from[i]) {
        ans[left][i] = bit.query(i) - bit.query(left - 1);
      }
    }

    for (const auto& [l, r] : queries) {
      cout << ans[l][r] << endl;
    }
  }
}
