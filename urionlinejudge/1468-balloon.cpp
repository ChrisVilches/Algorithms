#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  ll cross(const Point& p) const { return x * p.y - y * p.x; }
  Point to(const Point& p) const { return p - *this; }
};

struct Segment {
  Point p, q;
  Point to_vec() const { return p.to(q); }
  Point exit() const { return p.y > q.y ? p : q; }
  bool horizontal() const { return p.y == q.y; }
  bool operator<(const Segment& s) const {
    if (p.x < s.p.x)
      return to_vec().cross(p.to(s.p)) < 0;
    else
      return s.to_vec().cross(s.p.to(p)) > 0;
  }
};

vector<Segment> sort_segments(vector<Segment>& segments) {
  const int N = segments.size();

  sort(segments.begin(), segments.end(),
       [](const Segment& a, const Segment& b) { return a.p.x < b.p.x; });

  vector<vector<int>> graph(N + 1);

  set<pair<Segment, int>, greater<pair<Segment, int>>> s;

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

vector<Point> queries;
vector<Segment> segments;
int N, Q, parent[100'001];

set<pair<int, int>> queries_set;

int find(int u) {
  if (u != parent[u]) parent[u] = find(parent[u]);
  return parent[u];
}

void merge(int x, int y) { parent[find(x)] = find(y); }

void read_data() {
  segments.resize(N);
  queries.resize(Q);

  for (Segment& s : segments) {
    cin >> s.p.x >> s.p.y >> s.q.x >> s.q.y;
    if (s.p.x > s.q.x) swap(s.p, s.q);
  }

  for (int i = 0; i < Q; i++) {
    cin >> queries[i].x;
    queries[i].y = -1;
    queries_set.emplace(queries[i].x, i);
  }
}

void sweep_line() {
  vector<pii> removed;

  for (const Segment& segment : sort_segments(segments)) {
    while (!queries_set.empty()) {
      const auto it = queries_set.lower_bound({segment.p.x, -1});
      if (it == queries_set.end() || segment.q.x < it->first) break;

      auto [q_x, q_idx] = *it;

      if (segment.horizontal()) {
        queries[q_idx].y = segment.p.y;
      } else {
        q_x = segment.exit().x;
        queries[q_idx].x = segment.exit().x;
        removed.emplace_back(q_x, q_idx);
      }
      queries_set.erase(it);
    }

    if (removed.empty()) continue;

    for (const auto& [_, q_idx] : removed) {
      merge(q_idx, removed.front().second);
    }

    queries_set.emplace(removed.front());
    removed.clear();
  }
}

void print_result() {
  for (int i = 0; i < Q; i++) {
    const Point q = queries[find(i)];

    if (~q.y) {
      cout << q.x << ' ' << q.y << '\n';
    } else {
      cout << q.x << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N >> Q) {
    queries_set.clear();
    iota(parent, parent + Q, 0);

    read_data();
    sweep_line();
    print_result();
  }
}
