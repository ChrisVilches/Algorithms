#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld EPS = 1e-7;

struct Point {
  ld x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  ld cross(const Point& p) const { return x * p.y - y * p.x; }
  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
};

struct Segment {
  Point p, q;
};

bool equal(const ld a, const ld b) { return fabs(a - b) < EPS; }

vector<Segment> get_lines(const vector<Segment>& segments, const ld W, const ld H) {
  auto is_top = [&](const Point& p) { return equal(p.y, H); };
  auto is_bottom = [&](const Point& p) { return equal(p.y, 0); };
  auto is_right = [&](const Point& p) { return equal(p.x, W); };
  auto is_left = [&](const Point& p) { return equal(p.x, 0); };

  const Point center{W / 2, H / 2};

  vector<tuple<Point, int, Point>> events;

  for (int i = 0; i < (int)segments.size(); i++) {
    const Segment& s = segments[i];
    events.push_back({s.p - center, i, s.p});
    events.push_back({s.q - center, i, s.q});
  }

  sort(events.begin(), events.end());

  auto advance_point = [&](Point p, const bool advance = true) {
    const ld d = advance ? 0.5 : -0.5;
    if (is_top(p)) p.x -= d;
    if (is_right(p)) p.y += d;
    if (is_bottom(p)) p.x += d;
    if (is_left(p)) p.y -= d;
    return p;
  };

  vector<bool> side(segments.size());
  bool before_point = true;

  for (int i = 0, j = 1; i < (int)events.size(); i++) {
    const int curr_i = get<1>(events[i]);
    if (before_point) side[curr_i] = true;

    for (; j < (int)events.size(); j++) {
      const int curr_j = get<1>(events[j]);

      if (side[curr_j]) break;
      side[curr_j] = true;

      if (j - i == (int)segments.size()) {
        const Point p = advance_point(get<2>(events[i]), !before_point);
        const Point q = advance_point(get<2>(events[j]));

        return {Segment{p, q}};
      }
    }

    if (before_point) {
      before_point = false;
      side[curr_i] = false;
      i--;
    } else {
      before_point = true;
    }
  }

  const Segment diag1{{0.5, 0}, {W - 0.5, H}};
  const Segment diag2{{0.5, H}, {W - 0.5, 0}};
  return {diag1, diag2};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout << fixed << setprecision(2);

  int N;
  ld W, H;

  while (cin >> N >> W >> H) {
    vector<Segment> segments(N);

    for (Segment& s : segments) cin >> s.p.x >> s.p.y >> s.q.x >> s.q.y;

    const auto lines = get_lines(segments, W, H);

    cout << lines.size() << endl;

    for (const Segment& s : lines) {
      cout << s.p.x << " " << s.p.y << " " << s.q.x << " " << s.q.y << endl;
    }
  }
}
