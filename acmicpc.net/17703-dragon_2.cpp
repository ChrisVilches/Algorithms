#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y, idx, tribe;
  Point operator-(const Point p) const { return {x - p.x, y - p.y, idx, tribe}; }
  Point operator+(const Point p) const { return {x + p.x, y + p.y, idx, tribe}; }
  bool ccw(const Point p) const { return (long long)x * p.y - (long long)y * p.x > 0; }
  Point negate() const { return {-x, -y, idx, tribe}; }
};

template <class T, unsigned int N>
struct BIT {
  void clear(const int n) { memset(bit, 0, sizeof(T) * n); }

  T sum(int l, int r) { return sum(r) - sum(l - 1); }

  void add(unsigned int idx, const T delta) {
    for (; idx < N; idx = idx | (idx + 1)) bit[idx] += delta;
  }

 private:
  T bit[N];

  T sum(int r) {
    T ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
    return ret;
  }
};

BIT<int, 30'001> bit;
Point A, B;
vector<unordered_map<int, int>> ans;
vector<vector<Point>> tribes, order_by_b;

bool above(const Point p) { return B.ccw(p); }

Point to_upper(const Point p) { return above(p) ? p : p.negate(); }

bool operator<(const Point p, const Point q) { return to_upper(p).ccw(to_upper(q)); }

bool cmp(const Point p, const Point q) {
  return above(p) == above(q) ? p.ccw(q) : above(p);
}

void query(const int idx, const vector<Point>& multi_tribes, const bool single_attacker) {
  const vector<Point>& single_tribe = tribes[idx];
  const vector<Point>& ord = order_by_b[idx];

  bit.clear(single_tribe.size());

  const int mid = lower_bound(ord.begin(), ord.end(), B.negate(), cmp) - ord.begin();
  int j = 0;

  for (const Point p : multi_tribes) {
    while (j < (int)single_tribe.size() && single_tribe[j] < p) {
      bit.add(single_tribe[j++].idx, 1);
    }

    const int a = lower_bound(ord.begin(), ord.end(), p - B, cmp) - ord.begin();
    const int b = lower_bound(ord.begin(), ord.end(), B - p, cmp) - ord.begin();

    int& total = single_attacker ? ans[idx][p.tribe] : ans[p.tribe][idx];

    total += above(p) ? b - mid - bit.sum(mid, b - 1) : bit.sum(0, mid - 1) - b;

    if (single_attacker) {
      total += above(p) ? a - bit.sum(0, a - 1) : bit.sum(a, ord.size() - 1);
    } else {
      total += above(p) ? bit.sum(a, mid - 1) : a - mid - bit.sum(mid, a - 1);
    }
  }
}

void run_queries(const map<int, set<int>>& attacks, const map<int, set<int>>& attacked) {
  vector<tuple<long long, int, bool>> queries;

  const auto add_weighted_query = [&](const auto& q, const bool single_attacker) {
    const auto [tribe_idx, other] = q;
    const long long weight = tribes[tribe_idx].size() * other.size();
    queries.emplace_back(weight, tribe_idx, single_attacker);
  };

  for (const auto& q : attacks) add_weighted_query(q, true);
  for (const auto& q : attacked) add_weighted_query(q, false);

  sort(queries.rbegin(), queries.rend());

  for (const auto& [_, tribe_idx, single_attacker] : queries) {
    vector<Point> points;

    const auto& other_tribes = (single_attacker ? attacks : attacked).at(tribe_idx);

    for (const int tribe_idx2 : other_tribes) {
      int i = tribe_idx, j = tribe_idx2;
      if (!single_attacker) swap(i, j);

      if (ans[i].count(j)) continue;

      copy(tribes[tribe_idx2].begin(), tribes[tribe_idx2].end(), back_inserter(points));
      ans[i][j] = 0;
    }

    sort(points.begin(), points.end());
    query(tribe_idx, points, single_attacker);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N, M, Q;

  while (cin >> N >> M) {
    tribes.assign(M + 1, vector<Point>());
    order_by_b.assign(M + 1, vector<Point>());
    ans.assign(M + 1, unordered_map<int, int>());

    for (int i = 0; i < N; i++) {
      Point p;
      cin >> p.x >> p.y >> p.tribe;
      tribes[p.tribe].push_back(p);
    }

    cin >> A.x >> A.y >> B.x >> B.y;
    cin >> Q;
    B = B - A;

    for (int m = 1; m <= M; m++) {
      vector<Point>& points = tribes[m];
      for (Point& p : points) p = p - A - B;
      sort(points.begin(), points.end(), cmp);
      for (int i = 0; i < (int)points.size(); i++) points[i].idx = i;
      order_by_b[m] = points;
      for (Point& p : points) p = p + B;
      sort(points.begin(), points.end());
    }

    map<int, set<int>> attacks, attacked;
    vector<pair<int, int>> query_original_order;

    while (Q--) {
      int i, j;
      cin >> i >> j;
      attacks[i].emplace(j);
      attacked[j].emplace(i);
      query_original_order.emplace_back(i, j);
    }

    run_queries(attacks, attacked);

    for (const auto& [i, j] : query_original_order) {
      cout << ans[i][j] << '\n';
    }
  }
}
