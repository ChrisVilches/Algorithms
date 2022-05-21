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

vector<int> pre_order(const vector<vector<int>>& graph, const int root) {
  stack<int> dfs;
  vector<int> order;

  dfs.push(root);

  while (!dfs.empty()) {
    const int u = dfs.top();
    dfs.pop();

    order.push_back(u);

    for (const int v : graph[u]) dfs.push(v);
  }

  return order;
}

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

  const auto sorted_idx = pre_order(graph, N);

  vector<Segment> res;
  for (int i = 1; i <= N; i++) res.push_back(segments[sorted_idx[i]]);

  return res;
}

// TODO: Refactor????
class Delta {
  ll L, R;
  map<ll, int> asc, desc;

  map<ll, int>::iterator find_reverse(map<ll, int>& m, const ll val) {
    auto it = m.lower_bound(val);

    if (it != m.end() && it->first == val) return it;
    if (it != m.begin()) return prev(it);
    return m.end();
  }

  map<ll, int>::iterator find_first_right(map<ll, int>& m, const ll lo, const ll hi) {
    auto it = m.lower_bound(lo);
    return it == m.end() || hi < it->first ? m.end() : it;
  }

  map<ll, int>::iterator find_first_left(map<ll, int>& m, const ll lo, const ll hi) {
    auto it = find_reverse(m, hi);
    return it == m.end() || it->first < lo ? m.end() : it;
  }

  void add(map<ll, int>& m, const ll key, const int v) {
    m[key] += v;
    if (m[key] == 0) m.erase(key);
  }

  void minimize(const map<ll, int>::iterator a, const map<ll, int>::iterator d) {
    const int val = min(a->second, d->second);
    add(asc, a->first, -val);
    add(desc, d->first, -val);
  }

 public:
  Delta(const ll L, const ll R) : L(L), R(R) {
    const int inf = 1e7;
    asc[0] = inf;
    desc[L] = inf;
    asc[R + 1] = inf;
  }

  int minimum_query() const {
    int curr = 0;
    int result = INT_MAX;

    map<ll, int> total_delta{{L, 0}};

    for (const auto [x, d] : asc) total_delta[x] += d;
    for (const auto [x, d] : desc) total_delta[x] -= d;

    for (const auto [x, d] : total_delta) {
      if (x > R) break;
      curr += d;

      if (L <= x) result = min(result, curr);
    }
    return result;
  }

  void add_segment(const Segment& segment) {
    if (segment.flow_right()) {
      ll x = segment.p.x;

      while (true) {
        const auto asc_it = find_first_right(asc, x, segment.q.x);
        if (asc_it == asc.end()) break;

        x = asc_it->first;

        const auto desc_it = find_first_right(desc, x, segment.q.x);

        if (desc_it == desc.end()) {
          add(asc, segment.q.x + 1, asc_it->second);
          add(asc, asc_it->first, -asc_it->second);
        } else {
          minimize(asc_it, desc_it);
        }
      }

      asc[segment.p.x]++;
      desc[segment.q.x]++;
    } else {
      ll x = segment.q.x;

      while (true) {
        const auto desc_it = find_first_left(desc, segment.p.x, x);
        if (desc_it == desc.end()) break;

        x = desc_it->first;

        const auto asc_it = find_first_left(asc, segment.p.x, x);

        if (asc_it == asc.end()) {
          add(desc, segment.p.x - 1, desc_it->second);
          add(desc, desc_it->first, -desc_it->second);
        } else {
          minimize(asc_it, desc_it);
        }
      }

      asc[segment.p.x + 1]++;
      desc[segment.q.x + 1]++;
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int L, R, N;

  while (cin >> L >> R >> N) {
    L *= 2;
    R *= 2;
    L++;
    R++;

    vector<Segment> segments(N);

    for (int i = 0; i < N; i++) {
      Point p, q;
      cin >> p.x >> p.y >> q.x >> q.y;

      p.x *= 2;
      q.x *= 2;
      p.x++;
      q.x++;

      if (p.x > q.x) swap(p, q);
      segments[i].p = p;
      segments[i].q = q;
    }

    Delta d(L, R);

    for (const Segment& segment : sort_segments(segments)) d.add_segment(segment);

    cout << d.minimum_query() << endl;
  }
}
