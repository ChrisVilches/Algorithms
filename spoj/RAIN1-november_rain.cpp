#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline ll cross(const Point& p) const { return (x * p.y) - (y * p.x); }
  Point to(const Point& p) const { return p - *this; }
};

struct Segment {
  Point p, q;
  int original_idx;

  Point lowest_point() const { return p.y < q.y ? p : q; }

  bool operator<(const Segment& s) const {
    if (p.x < s.p.x)
      return p.to(q).cross(p.to(s.p)) < 0;
    else
      return s.p.to(s.q).cross(s.p.to(p)) > 0;
  }
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

    const auto it = s.insert({segments[i], i}).first;
    graph[it == s.begin() ? N : prev(it)->second].push_back(i);

    events.push({segments[i].q.x, i});
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

void solve() {
  int N;
  cin >> N;

  vector<Segment> segments(N);

  for (int i = 0; i < N; i++) {
    segments[i].original_idx = i;
    cin >> segments[i].p.x >> segments[i].p.y;
    cin >> segments[i].q.x >> segments[i].q.y;
  }

  set<pii> covered;
  map<int, ll> collected;

  vector<ll> ans(N);

  for (const Segment& s : sort_segments(segments)) {
    const int left = s.p.x;
    const int right = s.q.x;

    ans[s.original_idx] = right - left;

    pii new_covered{left, right};

    while (!covered.empty()) {
      auto it = covered.lower_bound({left, -1});
      if (it != covered.begin() && left < prev(it)->second) --it;

      auto const [from, to] = *it;
      if (right < from || to < left) break;

      ans[s.original_idx] -= min(to, right) - max(from, left);
      new_covered = {min(new_covered.first, from), max(new_covered.second, to)};
      covered.erase(it);
    }

    while (true) {
      const auto it = collected.lower_bound(left);
      if (it == collected.end() || right < it->first) break;

      ans[s.original_idx] += it->second;
      collected.erase(it);
    }

    covered.insert(new_covered);
    collected[s.lowest_point().x] = ans[s.original_idx];
  }

  for (ll a : ans) cout << a << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) solve();
}
