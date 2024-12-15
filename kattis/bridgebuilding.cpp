#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

struct BIT {
  BIT(const int n) : bit_n(n + 1) { A.assign(bit_n, 0); }

  ll range_sum(int l, int r) const {
    if (l > r) swap(l, r);
    return sum(r) - sum(l - 1);
  }

  ll sum(int i) const {
    i++;
    ll sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

  void update(int i, const ll v) {
    i++;
    for (; i < bit_n; i += i & -i) A[i] += v;
  }

 private:
  int bit_n;
  vector<ll> A;
};

struct RangeBIT {
  RangeBIT(const int n) : bit1(n), bit2(n) {}

  void update_range(const ll l, const ll r, const ll v) {
    bit1.update(l, v);
    bit1.update(r + 1, -v);
    bit2.update(l, -v * (l - 1));
    bit2.update(r + 1, v * r);
  }

  void clear(const int i) { update_range(i, i, -range_sum(i, i)); }

  ll range_sum(const ll l, const ll r) const {
    const ll a = bit1.sum(r) * r + bit2.sum(r);
    const ll b = bit1.sum(l - 1) * (l - 1) + bit2.sum(l - 1);
    return a - b;
  }

 private:
  BIT bit1, bit2;
};

vector<ll> height_psum;
vector<int> heights;
map<int, pii> curr_bridges_by_right;

BIT bit_count(0), bit_dist(0);
RangeBIT bit_vertical(0), bit_vertical_count(0);

vector<pii> generate_bridges() {
  stack<int> s;
  vector<pii> res;

  for (int j = 0; j < (int)heights.size(); j++) {
    const int h = heights[j];

    while (!s.empty() && heights[s.top()] < h) s.pop();

    if (!s.empty() && heights[s.top()] == h) {
      const int i = s.top();
      if (j - i > 1) res.emplace_back(i, j);
      s.pop();
    }

    s.push(j);
  }

  return res;
}

ll dist(int a, int b) {
  if (a > b) swap(a, b);
  return b - a + height_psum[b] - height_psum[a];
}

ll dist(const pii& p) { return dist(p.first, p.second); }

int bridge_breakpoint(const pii& bridge, const bool left) {
  const ll bridge_size = bridge.second - bridge.first;
  auto [lo, hi] = bridge;
  while (lo <= hi) {
    const int mid = (lo + hi) / 2;
    const ll first = dist(bridge.first, mid) + (left ? bridge_size : 0);
    const ll second = dist(mid, bridge.second) + (left ? 0 : bridge_size);

    if (first < second) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  return left ? hi : lo;
}

ll partially_contained_pairs_benefit(const pii& bridge, const bool left) {
  const int endpoint = left ? bridge.first : bridge.second;
  const int opposite_endpoint = left ? bridge.second : bridge.first;
  const int breakpoint = bridge_breakpoint(bridge, left);
  const ll n = bit_count.range_sum(endpoint, breakpoint);
  const ll sum = bit_dist.range_sum(endpoint, breakpoint);

  const ll original_route = abs(sum - n * dist(0, opposite_endpoint));
  const ll alternative_route =
      n * (bridge.second - bridge.first) + abs(n * dist(0, endpoint) - sum);

  return original_route - alternative_route;
}

pii vertical_range(const pii& p) {
  const auto it = curr_bridges_by_right.lower_bound(p.second);
  if (it == curr_bridges_by_right.end()) return {-1, -1};

  const int h0 = heights[it->second.first];
  int h1 = -1;

  int lo = p.second;
  int hi = prev(curr_bridges_by_right.end())->second.second;

  while (lo <= hi) {
    const int mid = (lo + hi) / 2;
    const pii bridge = curr_bridges_by_right.lower_bound(mid)->second;
    const ll bridge_size = bridge.second - bridge.first;

    if (bridge_size + dist(bridge) < 2 * dist(p)) {
      lo = mid + 1;
      h1 = heights[bridge.first];
    } else {
      hi = mid - 1;
    }
  }
  return h1 == -1 ? pii{-1, -1} : pii{h0, h1};
}

ll fully_contained_pairs_benefit(const pii& bridge) {
  const int h = heights[bridge.first];
  const ll n = bit_vertical_count.range_sum(h, h);
  const ll bridge_size = bridge.second - bridge.first;
  const ll original_route = bit_vertical.range_sum(h, h);
  const ll alternative_route = (n * (bridge_size + dist(bridge))) - original_route;
  return original_route - alternative_route;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;

  while (cin >> n >> m) {
    heights.resize(n);
    curr_bridges_by_right.clear();
    for (auto& h : heights) cin >> h;

    height_psum.assign(1, 0);
    for (int i = 0; i < n - 1; i++) {
      const int dh = abs(heights[i] - heights[i + 1]);
      height_psum.emplace_back(height_psum.back() + dh);
    }

    bit_count = BIT(n);
    bit_dist = BIT(n);

    const int bit_size = *max_element(heights.begin(), heights.end()) + 1;
    bit_vertical = RangeBIT(bit_size);
    bit_vertical_count = RangeBIT(bit_size);

    ll total_cost = 0;
    vector<pii> pairs(m);
    for (auto& p : pairs) {
      cin >> p.first >> p.second;
      p.first--;
      p.second--;
      if (p.first > p.second) swap(p.first, p.second);
      total_cost += dist(p);
    }

    map<pii, ll> benefit;

    unordered_map<int, pii> start_bridge_events, close_bridge_events;
    unordered_map<int, vector<int>> pair_events;

    for (const auto& bridge : generate_bridges()) {
      start_bridge_events[bridge.first] = bridge;
      close_bridge_events[bridge.second] = bridge;
    }

    for (int i = 0; i < m; i++) {
      pair_events[pairs[i].first].emplace_back(i);
      pair_events[pairs[i].second].emplace_back(i);
    }

    vector<bool> curr_pairs(m, false);

    for (int ev_pos = 0; ev_pos < n; ev_pos++) {
      for (const auto& pair_idx : pair_events[ev_pos]) {
        curr_pairs[pair_idx] = !curr_pairs[pair_idx];
        const bool enter = curr_pairs[pair_idx];

        const ll sgn = enter ? 1 : -1;

        const pii p = pairs[pair_idx];
        bit_count.update(p.first, sgn);
        bit_count.update(p.second, sgn);
        bit_dist.update(p.first, sgn * dist(0, p.first));
        bit_dist.update(p.second, sgn * dist(0, p.second));

        if (enter) {
          const auto [h0, h1] = vertical_range(p);
          if (h0 == -1) continue;

          bit_vertical.update_range(h0, h1, dist(p));
          bit_vertical_count.update_range(h0, h1, 1);
        }
      }

      if (close_bridge_events.count(ev_pos)) {
        const pii bridge = close_bridge_events[ev_pos];
        curr_bridges_by_right.erase(bridge.second);
        const ll bridge_size = bridge.second - bridge.first;
        benefit[bridge] += fully_contained_pairs_benefit(bridge);
        benefit[bridge] += bit_count.sum(bridge.first - 1) * (dist(bridge) - bridge_size);
        benefit[bridge] += partially_contained_pairs_benefit(bridge, true);
      }

      if (start_bridge_events.count(ev_pos)) {
        const pii bridge = start_bridge_events[ev_pos];
        curr_bridges_by_right[bridge.second] = bridge;
        bit_vertical.clear(heights[bridge.first]);
        bit_vertical_count.clear(heights[bridge.first]);
        benefit[bridge] += partially_contained_pairs_benefit(bridge, false);
      }
    }

    const ll max_benefit =
        max_element(benefit.begin(), benefit.end(), [](const auto& a, const auto& b) {
          return a.second < b.second;
        })->second;

    cout << total_cost - max_benefit << endl;
  }
}
