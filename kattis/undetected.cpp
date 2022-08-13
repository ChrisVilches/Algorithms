#include <bits/stdc++.h>
using namespace std;

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

struct Circle {
  double x, y, r;

  bool intersects(const Circle& c) const {
    const double center_dist = hypot(x - c.x, y - c.y);
    const double radius_sum = r + c.r;
    return center_dist < radius_sum;
  }
} circles[201];

const int X = 200;

bool can_cross(const int K) {
  DisjointSets ds(K);

  for (int i = 0; i < K; i++)
    for (int j = i + 1; j < K; j++)
      if (circles[i].intersects(circles[j])) ds.merge(i, j);

  vector<int> out_left, out_right;

  for (int i = 0; i < K; i++) {
    const int min_x = circles[i].x - circles[i].r;
    const int max_x = circles[i].x + circles[i].r;

    if (min_x < 0) {
      out_left.push_back(i);
      for (const int r : out_right)
        if (ds.find(r) == ds.find(i)) return false;
    }

    if (X < max_x) {
      out_right.push_back(i);
      for (const int l : out_left)
        if (ds.find(l) == ds.find(i)) return false;
    }
  }

  return true;
}

int main() {
  int N;

  while (cin >> N) {
    for (int i = 0; i < N; i++) cin >> circles[i].x >> circles[i].y >> circles[i].r;

    int ans = 0;

    for (int k = 1; k <= N; k++)
      if (can_cross(k)) ans = k;

    cout << ans << endl;
  }
}
