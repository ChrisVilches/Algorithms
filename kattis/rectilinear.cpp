// NOTE: Weak test data.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  int idx;
};

bool cmp1(const Point p, const Point q) { return p.x < q.x || (p.x == q.x && p.y < q.y); }
bool cmp2(const Point p, const Point q) { return p.y < q.y || (p.y == q.y && p.x < q.x); }

struct DisjointSets {
  DisjointSets(int n) : parent(n), rank(n, 0) { iota(parent.begin(), parent.end(), 0); }

  int find(const int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (rank[x] > rank[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rank[x] == rank[y]) rank[y]++;
  }

 private:
  vector<int> parent, rank;
};

bool edges_connected(vector<Point> points) {
  const int n = points.size();
  DisjointSets ds(n);
  sort(points.begin(), points.end(), cmp1);

  for (int sw = 0; sw < 2; sw++) {
    for (int i = 0; i < (int)points.size() - 1; i += 2) {
      ds.merge(points[i].idx, points[i + 1].idx);
    }

    sort(points.begin(), points.end(), cmp2);
  }

  for (int i = 1; i < n; i++) {
    if (ds.find(0) != ds.find(i)) return false;
  }

  return true;
}

bool check_can_build(vector<Point> points) {
  map<ll, ll> state;
  sort(points.begin(), points.end(), cmp1);

  for (const auto& [x, y, _] : points) {
    if (state.count(y)) {
      state.erase(y);
    } else {
      state[y] = x;
    }
  }

  return state.empty();
}

ll calculate_perimeter(vector<Point> points) {
  ll total = 0;

  sort(points.begin(), points.end(), cmp1);

  for (int i = 0; i < (int)points.size() - 1; i += 2) {
    total += points[i + 1].y - points[i].y;
  }

  sort(points.begin(), points.end(), cmp2);

  for (int i = 0; i < (int)points.size() - 1; i += 2) {
    total += points[i + 1].x - points[i].x;
  }

  return total;
}

ll solve() {
  int n;
  cin >> n;
  vector<Point> points(n);
  for (int i = 0; i < n; i++) {
    cin >> points[i].x >> points[i].y;
    points[i].idx = i;
  }

  if (!edges_connected(points)) return -1;
  if (!check_can_build(points)) return -1;

  return calculate_perimeter(points);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    cout << solve() << endl;
  }
}
