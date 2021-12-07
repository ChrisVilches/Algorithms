#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

#define INF (1LL << 50)
const int MAX = 10001;
int N, H, ALPHA, BETA;
ld arc_left_max[MAX], arc_right_max[MAX];
ll memo[MAX];

struct Point {
  ll x, y;
} ground[MAX];

ll dist(int i, int j) { return abs(ground[i].x - ground[j].x); }
ll pillar_height(int i) { return H - ground[i].y; }
ll cost_pillar(int i) { return ALPHA * pillar_height(i); }
ll cost_arc(int i, int j) { return BETA * pow(dist(i, j), 2); }

// Includes the cost of only the left pillar (plus the arc).
ll cost(int i, int j) { return cost_pillar(i) + cost_arc(i, j); }

bool arc_ok(int i, int j) {
  ld arc_radius = (ld)dist(i, j) / 2L;
  return arc_right_max[i] >= arc_radius && arc_left_max[j] >= arc_radius;
}

void precompute_arc_bounds_right(const int point) {
  ld r = H - ground[point].y;
  for (int i = point + 1; i < N; i++) {
    ld center_x = ground[point].x + r;
    ld center_y = H - r;
    if (center_x < ground[i].x) break;
    ld circle_y = sqrt(pow(r, 2) - pow(ground[i].x - center_x, 2)) + center_y;
    if (circle_y > ground[i].y) continue;
    auto [L, X, Y] = tie(ground[point].x, ground[i].x, ground[i].y);
    r = H - L + X - Y + sqrt(2) * sqrt(-H * L + H * X + L * Y - X * Y);
  }

  arc_right_max[point] = r;
}

void precompute_arc_bounds_left(const int point) {
  ld r = H - ground[point].y;
  for (int i = point - 1; i >= 0; i--) {
    ld center_x = ground[point].x - r;
    ld center_y = H - r;
    if (ground[i].x < center_x) break;
    ld circle_y = sqrt(pow(r, 2) - pow(ground[i].x - center_x, 2)) + center_y;
    if (circle_y > ground[i].y) continue;
    auto [R, X, Y] = tie(ground[point].x, ground[i].x, ground[i].y);
    r = H + R - X - Y + sqrt(2) * sqrt(H * R - H * X - R * Y + X * Y);
  }

  arc_left_max[point] = r;
}

ll dp(int n) {
  if (~memo[n]) return memo[n];

  ll min_cost = arc_ok(n, N - 1) ? cost(n, N - 1) + cost_pillar(N - 1) : INF;

  for (int i = n + 1; i < N - 1; i++)
    min_cost = min(min_cost, arc_ok(n, i) ? cost(n, i) + dp(i) : INF);

  return memo[n] = min_cost;
}

int main() {
  scanf("%d %d %d %d", &N, &H, &ALPHA, &BETA);
  memset(memo, -1, sizeof memo);

  for (int i = 0; i < N; i++) scanf("%lld %lld", &ground[i].x, &ground[i].y);

  for (int i = 1; i < N; i++) precompute_arc_bounds_left(i);
  for (int i = 0; i < N - 1; i++) precompute_arc_bounds_right(i);

  ll result = dp(0);

  if (result == INF)
    cout << "impossible" << endl;
  else
    cout << result << endl;
}
