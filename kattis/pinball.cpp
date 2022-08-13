#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline ll cross(const Point& p) const { return x * p.y - y * p.x; }
  Point to(const Point& p) const { return p - *this; }
};

struct Segment {
  Point p, q;
  Point to_vec() const { return p.to(q); }

  bool operator<(const Segment& s) const {
    if (p.x < s.p.x)
      return to_vec().cross(p.to(s.p)) < 0;
    else
      return s.to_vec().cross(s.p.to(p)) > 0;
  }

  bool flow_right() const { return p.y > q.y; }
};

vector<Segment> sort_segments(vector<Segment>& segments) {
  const int N = segments.size();

  sort(segments.begin(), segments.end(),
       [](const Segment& a, const Segment& b) { return a.p.x < b.p.x; });

  vector<vector<int>> graph(N + 1);

  set<pair<Segment, int>> s;

  priority_queue<pii, vector<pii>, greater<pii>> events;

  for (int i = 0; i < N; i++) {
    while (!events.empty() && events.top().first < segments[i].p.x) {
      const int idx = events.top().second;
      s.erase({segments[idx], idx});
      events.pop();
    }

    const auto it = s.emplace(segments[i], i).first;
    graph[it == s.begin() ? N : prev(it)->second].push_back(i);

    events.emplace(segments[i].q.x, i);
  }

  vector<Segment> res;

  stack<int> dfs;
  dfs.push(N);

  while (!dfs.empty()) {
    const int u = dfs.top();
    dfs.pop();

    if (u != N) res.push_back(segments[u]);
    for (const int v : graph[u]) dfs.push(v);
  }

  return res;
}

int main() {
  int N;

  while (cin >> N) {
    vector<Segment> segments(N);

    for (auto& s : segments) {
      cin >> s.p.x >> s.p.y >> s.q.x >> s.q.y;
      if (s.p.x > s.q.x) swap(s.p, s.q);
    }

    ll x;
    cin >> x;

    for (const Segment& s : sort_segments(segments)) {
      if (s.p.x <= x && x <= s.q.x) {
        x = s.flow_right() ? s.q.x : s.p.x;
      }
    }

    cout << x << endl;
  }
}
