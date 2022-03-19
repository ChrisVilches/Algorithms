#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline ll operator^(const Point& p) const { return (x * p.y) - (y * p.x); }
  Point to(const Point& p) const { return p - *this; }
};

struct Segment {
  Point p, q;
  static Segment from_stdin() {
    Segment s;
    cin >> s.p.x >> s.p.y >> s.q.x >> s.q.y;
    return s;
  }
  Point lowest_point() const { return p.y < q.y ? p : q; }
  Point to_vec() const { return p.to(q); }

  bool operator<(const Segment& s) const {
    if (q.x < s.p.x) {
      return (to_vec() ^ (q.to(s.p))) > 0;
    } else {
      return (to_vec() ^ p.to(s.q)) > 0;
    }
  }
};

vector<int> toposort(const vector<vector<int>>& graph) {
  vector<int> order;
  vector<bool> visited(graph.size(), false);

  function<void(int)> dfs = [&](const int u) {
    if (visited[u]) return;
    visited[u] = true;

    for (const int v : graph[u]) dfs(v);
    order.push_back(u);
  };

  for (int i = 0; i < (int)graph.size(); i++) dfs(i);

  reverse(order.begin(), order.end());

  return order;
}

vector<int> sort_segments(const vector<Segment>& segments) {
  vector<tuple<ll, ll, int>> events;

  for (int i = 0; i < (int)segments.size(); i++) {
    const Segment& s = segments[i];
    events.push_back({s.p.x - 1, s.p.y, i});
    events.push_back({s.q.x + 1, s.q.y, i});
  }

  sort(events.begin(), events.end());

  set<int> active;

  vector<vector<int>> graph(segments.size());

  for (const auto& [_x, _y, idx] : events) {
    if (active.count(idx)) {
      active.erase(idx);
      continue;
    }

    for (const int active_segment_idx : active) {
      const Segment& s = segments[active_segment_idx];

      if ((s.to_vec() ^ s.p.to(segments[idx].p)) > 0) {
        graph[idx].push_back(active_segment_idx);
      } else {
        graph[active_segment_idx].push_back(idx);
      }
    }

    active.insert(idx);
  }

  return toposort(graph);
}

void solve() {
  int N;
  cin >> N;

  vector<Segment> segments;

  for (int i = 0; i < N; i++) segments.push_back(Segment::from_stdin());

  set<pair<int, int>> covered;
  map<int, ll> collected;

  vector<ll> ans(N);

  for (const int idx : sort_segments(segments)) {
    // sort(segments.rbegin(), segments.rend());
    // for (int idx = 0; idx < (int)segments.size(); idx++) {
    const Segment& s = segments[idx];
    const int left = s.p.x;
    const int right = s.q.x;

    ans[idx] = right - left;

    int covered_left = left;
    int covered_right = right;

    while (!covered.empty()) {
      auto it = covered.lower_bound({left, -1});

      if (it == covered.end() ||
          (it->first != left && it != covered.begin() && left < prev(it)->second)) {
        it--;
      }

      auto const [from, to] = *it;

      if (right < from || to < left) break;

      ans[idx] -= min(to, right) - max(left, from);

      covered_left = min(from, covered_left);
      covered_right = max(to, covered_right);

      covered.erase(it);
    }

    covered.emplace(covered_left, covered_right);

    while (true) {
      const auto it = collected.lower_bound(left);
      if (it == collected.end() || right < it->first) break;

      ans[idx] += it->second;
      collected.erase(it);
    }

    collected[s.lowest_point().x] = ans[idx];
  }

  for (ll a : ans) cout << a << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) solve();
}
