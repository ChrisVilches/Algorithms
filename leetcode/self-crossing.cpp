#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator*(const int f) const { return {x * f, y * f}; }
  bool operator==(const Point p) const { return x == p.x && y == p.y; }
  bool operator<(const Point p) const { return x < p.x || (x == p.x && y < p.y); }
};

struct Segment {
  Point p, q;
  int bottom() const { return min(p.y, q.y); }
  int top() const { return max(p.y, q.y); }
  int left() const { return min(p.x, q.x); }
  int right() const { return max(p.x, q.x); }
  bool operator<(const Segment s) const { return left() < s.left(); }
  bool horizontal() const { return p.y == q.y; }
  bool intersects(const Segment s) const {
    if (p == s.p || p == s.q || q == s.p || q == s.q) return false;
    if (horizontal() == s.horizontal()) return false;
    const Segment ver = horizontal() ? s : *this;
    const Segment hor = horizontal() ? *this : s;
    if (hor.p.y < ver.bottom() || hor.p.y > ver.top()) return false;
    if (ver.p.x < hor.left() || hor.right() < ver.p.x) return false;
    return true;
  }
};

class Solution {
  bool overlap(const vector<pair<int, int>>& ranges) {
    vector<pair<int, int>> events;
    for (const auto& [start, end] : ranges) {
      events.emplace_back(start, 1);
      events.emplace_back(end, -1);
    }
    sort(events.begin(), events.end());
    int curr = 0;
    for (const auto& [_, d] : events) {
      curr += d;
      if (curr > 1) return true;
    }
    return false;
  }

 public:
  bool isSelfCrossing(const vector<int>& distance) {
    vector<Segment> segments;

    map<Point, int> freq;
    freq[{0, 0}]++;
    const array<Point, 4> dir{Point{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

    for (const int d : distance) {
      const Point p = segments.empty() ? Point{0, 0} : segments.back().q;
      const Point q = p + dir[segments.size() % 4] * d;

      freq[q]++;
      if (freq[q] > 1) return true;
      segments.push_back(Segment{p, q});
    }

    unordered_map<int, vector<pair<int, int>>> vertical_groups;
    for (const Segment s : segments) {
      if (!s.horizontal()) {
        vertical_groups[s.left()].emplace_back(s.bottom(), s.top());
      }
    }

    for (const auto& [_, ranges] : vertical_groups) {
      if (overlap(ranges)) return true;
    }

    map<int, Segment> active;
    vector<tuple<int, Segment, bool>> horizontal;
    vector<Segment> vertical;

    for (const Segment s : segments) {
      if (s.horizontal()) {
        horizontal.emplace_back(s.left(), s, true);
        horizontal.emplace_back(s.right(), s, false);
      } else {
        vertical.emplace_back(s);
      }
    }

    sort(horizontal.begin(), horizontal.end());
    sort(vertical.begin(), vertical.end());

    auto it = vertical.begin();

    for (const auto& [x, hor_seg, enter] : horizontal) {
      if (enter) {
        active[hor_seg.bottom()] = hor_seg;
        continue;
      }

      for (; it != vertical.end() && it->left() <= x; it++) {
        const auto found = active.lower_bound(it->bottom());
        if (found != active.end()) {
          if (it->intersects(found->second)) return true;
        }
      }
    }

    return false;
  }
};
