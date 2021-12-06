#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point(ll x, ll y) : x(x), y(y) {}
  Point() {}
  inline int quad() const { return y != 0 ? (y > 0) : x > 0; }
  inline bool operator<(const Point& p) const {
    return quad() != p.quad() ? quad() > p.quad() : (*this ^ p) > 0;
  }
  inline Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline bool operator!=(const Point& p) const { return x != p.x || y != p.y; }
  inline void operator-=(const Point& p) { x -= p.x, y -= p.y; }
  inline ll operator^(const Point& p) const { return x * p.y - y * p.x; }
};

struct Rock {
  vector<Point> vertices;
  Point endpoint_a, endpoint_b;

  void compute_endpoints() {
    sort(vertices.begin(), vertices.end(),
         [](const Point& p, const Point& q) { return (p ^ q) > 0; });
    endpoint_a = vertices.front();
    endpoint_b = vertices.back();
  }

  bool intersects_positive_x_axis() const { return endpoint_b < endpoint_a; }
};

int N, R, ev_n, curr_rocks_count;
Rock rocks[30001];
bool curr_rocks[30001];
pair<Point, int> events[2 * 30001];
Point origin, posts[4 * 500'201];

inline void toggle_rock(int rock_idx) {
  curr_rocks[rock_idx] = !curr_rocks[rock_idx];
  curr_rocks_count += curr_rocks[rock_idx] ? 1 : -1;
}

int radial_sweep() {
  int visible = 0;
  int p = 0;

  for (int i = 0; i < ev_n; i++) {
    int r_idx = events[i].second;
    if (!curr_rocks[r_idx] && rocks[r_idx].intersects_positive_x_axis())
      toggle_rock(r_idx);
  }

  for (int i = 0; i < ev_n; i++) {
    auto [rock, r_idx] = events[i];

    for (; posts[p] < rock || (curr_rocks[r_idx] && !(posts[p] ^ rock)); p++)
      visible += (curr_rocks_count == 0);

    toggle_rock(r_idx);
  }

  return curr_rocks_count ? visible : (visible + 4 * N - p);
}

void generate_posts(Point& origin) {
  int i = 0;
  posts[i++] = {N, origin.y};
  while (posts[i - 1] != Point(N, N)) posts[i++] = {N, posts[i - 1].y + 1};
  while (posts[i - 1] != Point{0, N}) posts[i++] = {posts[i - 1].x - 1, N};
  while (posts[i - 1] != Point{0, 0}) posts[i++] = {0, posts[i - 1].y - 1};
  while (posts[i - 1] != Point(N, 0)) posts[i++] = {posts[i - 1].x + 1, 0};
  while (posts[i - 1] != Point{N, origin.y})
    posts[i++] = {N, posts[i - 1].y + 1};

  for (int p = 0; p < 4 * N; p++) posts[p] -= origin;
}

int main() {
  scanf("%d %d %lld %lld", &N, &R, &origin.x, &origin.y);
  generate_posts(origin);

  for (int i = 0; i < R; i++) {
    int p;
    scanf("%d", &p);
    while (p--) {
      Point v;
      scanf("%lld %lld", &v.x, &v.y);
      rocks[i].vertices.push_back(v - origin);
    }
    rocks[i].compute_endpoints();
    events[ev_n++] = make_pair(rocks[i].endpoint_a, i);
    events[ev_n++] = make_pair(rocks[i].endpoint_b, i);
  }

  sort(events, events + ev_n);
  printf("%d\n", radial_sweep());
}
