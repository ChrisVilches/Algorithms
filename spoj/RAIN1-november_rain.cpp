#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const ll INF = 1LL << 31;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline ll cross(const Point& p) const { return (x * p.y) - (y * p.x); }
  Point to(const Point& p) const { return p - *this; }
};

struct Segment {
  Point p, q;
  int original_idx = -1;

  static Segment from_stdin(const int idx) {
    Segment s;
    s.original_idx = idx;
    cin >> s.p.x >> s.p.y >> s.q.x >> s.q.y;
    return s;
  }
  Point lowest_point() const { return p.y < q.y ? p : q; }
  Point to_vec() const { return p.to(q); }

  bool operator<(const Segment& s) const {
    if (p.x < s.p.x)
      return to_vec().cross(p.to(s.p)) < 0;
    else
      return s.to_vec().cross(s.p.to(p)) > 0;
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

vector<Segment> sort_segments(vector<Segment>& segments) {
  const int N = segments.size();

  sort(segments.begin(), segments.end(),
       [](const Segment& a, const Segment& b) { return a.p.x < b.p.x; });

  vector<vector<int>> graph(N + 1);

  const Segment above{Point{-1, INF}, Point{INF, INF}};

  set<pair<Segment, int>> s{{above, N}};

  priority_queue<pii, vector<pii>, greater<pii>> events;

  for (int i = 0; i < N; i++) {
    while (!events.empty() && events.top().first < segments[i].p.x) {
      const int idx = events.top().second;
      s.erase({segments[idx], idx});
      events.pop();
    }

    const auto it = s.insert({segments[i], i}).first;
    graph[prev(it)->second].push_back(i);

    events.push({segments[i].q.x, i});
  }

  const auto sorted_idx = toposort(graph);

  vector<Segment> res;
  for (int i = 1; i <= N; i++) res.push_back(segments[sorted_idx[i]]);

  return res;
}

void solve() {
  int N;
  cin >> N;

  vector<Segment> segments;

  for (int i = 0; i < N; i++) segments.push_back(Segment::from_stdin(i));

  set<pii> covered;
  map<int, ll> collected;

  vector<ll> ans(N);

  for (const Segment& s : sort_segments(segments)) {
    const int left = s.p.x;
    const int right = s.q.x;

    ans[s.original_idx] = right - left;

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

      ans[s.original_idx] -= min(to, right) - max(left, from);

      covered_left = min(from, covered_left);
      covered_right = max(to, covered_right);

      covered.erase(it);
    }

    covered.emplace(covered_left, covered_right);

    while (true) {
      const auto it = collected.lower_bound(left);
      if (it == collected.end() || right < it->first) break;

      ans[s.original_idx] += it->second;
      collected.erase(it);
    }

    collected[s.lowest_point().x] = ans[s.original_idx];
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
