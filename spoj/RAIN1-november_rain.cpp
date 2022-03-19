#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline ll operator^(const Point& p) const { return (x * p.y) - (y * p.x); }
  Point to(const Point& p) const { return p - *this; }
};

struct Segment {
  int idx;
  int original_idx;
  Point p, q;
  static Segment from_stdin() {
    Segment s;
    cin >> s.p.x >> s.p.y >> s.q.x >> s.q.y;
    return s;
  }
  Point lowest_point() const { return p.y < q.y ? p : q; }
  Point to_vec() const { return p.to(q); }

  bool operator<(const Segment& s) const {
    if (p.x < s.p.x) {
      // THIS enters first (in the sweep line)
      return (to_vec() ^ p.to(s.p)) < 0;
    } else {
      return (s.to_vec() ^ s.p.to(p)) > 0;
    }

    /*
    ll X1 = p.x;
    ll Y1 = p.y;
    ll X2 = q.x;
    ll Y2 = q.y;

    ll tX1 = t.p.x;
    ll tY1 = t.p.y;
    ll tX2 = t.q.x;
    ll tY2 = t.q.y;

    bool ret;

    if (X1 > tX1) {
      ret = (Y1 - tY1) * (tX2 - tX1) < (X1 - tX1) * (tY2 - tY1);
    } else {
      ret = (tY1 - Y1) * (X2 - X1) > (tX1 - X1) * (Y2 - Y1);
    }

    return !ret;*/
  }

  /*
    bool operator<(const Segment& s) const {
      if (q.x < s.p.x) {
        return (to_vec() ^ (q.to(s.p))) < 0;
      } else {
        return (to_vec() ^ p.to(s.q)) < 0;
      }
    }*/
};

vector<int> toposort(const vector<vector<int>>& graph) {
  vector<int> order;
  vector<bool> visited(graph.size(), false);

  function<void(int)> dfs = [&](const int u) {
    if (visited[u]) return;
    visited[u] = true;

    for (const int v : graph.at(u)) dfs(v);
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
  for (int i = 0; i < N; i++) segments[i].original_idx = i;

  set<pii> covered;
  map<int, ll> collected;

  vector<ll> ans(N);

  sort(segments.begin(), segments.end(),
       [](const Segment& a, const Segment& b) { return a.p.x < b.p.x; });

  vector<vector<int>> graph(N + 1);

  for (int i = 0; i < N; i++) segments[i].idx = i;
  set<Segment> s;
  priority_queue<pii, vector<pii>, greater<pii>> events;

  for (int i = 0; i < N; i++) {
    while (!events.empty() && events.top().first < segments[i].p.x) {
      s.erase(segments.at(events.top().second));
      events.pop();
    }

    auto it = s.insert(segments[i]).first;

    if (it == s.begin())
      graph[N].push_back(i);
    else
      graph.at((--it)->idx).push_back(i);

    events.push({segments[i].q.x, i});
  }

  // cerr << "World" << endl;

  // cerr << "<toposort>" << endl;

  auto toposorted = toposort(graph);
  // cerr << "N = " << N << endl;
  // for (int xx : toposorted) {
  //   cerr << xx << " ";
  //}/
  // cerr << endl;
  // cerr << "</toposort>" << endl;

  // cerr << "<loop>" << endl;

  // for (const int idx : sort_segments(segments)) {
  for (int iii = 1; iii < (int)toposorted.size(); iii++) {
    int idx = toposorted[iii];
    //  sort(segments.rbegin(), segments.rend());
    //  for (int idx = 0; idx < (int)segments.size(); idx++) {
    const Segment& s = segments.at(idx);
    const int left = s.p.x;
    const int right = s.q.x;

    ans.at(s.original_idx) = right - left;

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

  // cerr << "</loop>" << endl;

  for (ll a : ans) cout << a << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) solve();
}
