#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  long long cross(const Point& p) const {
    return (long long)x * p.y - (long long)y * p.x;
  }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  bool operator<(const Point& p) const { return cross(p) > 0; }
};

int N, M, K;
int points_outside[403][403];
int memo[403][403][403];

void compute_outside(const int idx, const Point center, const deque<Point>& polygon,
                     const vector<Point>& points) {
  auto point_it = points.begin();

  for (int i = 0; i < (int)polygon.size(); i++) {
    const int original_idx = (idx + 1 + i) % M;

    const Point vertex = polygon[i];

    while (point_it != points.end() && (vertex - center).cross(*point_it - center) <= 0)
      point_it++;

    points_outside[idx][original_idx] = distance(points.begin(), point_it);
  }
}

const int INF = 1e5;

int dp(const int curr_idx, const int init_idx, const int K) {
  if (K < 0) return INF;
  if (curr_idx - init_idx > M) return INF;
  if (curr_idx - init_idx == M) return 0;

  int& m = memo[curr_idx % M][init_idx % M][K];

  if (~m) return m;

  int res = INF;

  for (int i = curr_idx + 1, it = M - 1; it--; i++) {
    const int outside = points_outside[curr_idx % M][i % M];
    const int next_state = dp(i, init_idx, K - 1);

    res = min(res, outside + next_state);
  }

  return m = res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N >> M >> K) {
    vector<Point> points(N);
    deque<Point> polygon(M);
    K = min(M, K);
    memset(memo, -1, sizeof memo);

    for (auto& p : points) cin >> p.x >> p.y;
    for (auto& p : polygon) cin >> p.x >> p.y;
    reverse(polygon.begin(), polygon.end());

    for (int i = 0; i < M; i++) {
      const Point pivot = polygon.front();
      polygon.pop_front();

      sort(points.begin(), points.end(),
           [pivot](const Point& p, const Point& q) { return p - pivot < q - pivot; });

      compute_outside(i, pivot, polygon, points);

      polygon.push_back(pivot);
    }

    int min_removed = INF;

    for (int i = 0; i < M / K; i++) {
      min_removed = min(min_removed, dp(i, i, K));
    }

    cout << N - min_removed << endl;
  }
}
