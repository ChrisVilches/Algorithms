#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int deltas[100007];
int ans[100007];

struct DisjointSets {
  DisjointSets(int n) : parent(vector<int>(n)) { iota(parent.begin(), parent.end(), 0); }

  int find(int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  // Union without rank.
  void merge(int x, int y) { parent[find(x)] = find(y); }

 private:
  vector<int> parent;
};

struct Query {
  const int idx;
  ll offset;
  Query(int idx, ll offset) : idx(idx), offset(offset) {}
  ll get_value(ll global_sum) const { return offset + global_sum; }
  bool operator<(const Query& q) const {
    return offset < q.offset || (offset == q.offset && idx < q.idx);
  }
};

int N, Q;

void solve() {
  ll L, U;
  cin >> L >> U;
  for (int i = 0; i < N; i++) cin >> deltas[i];

  cin >> Q;

  vector<Query> queries;

  set<pair<int, int>> start_times, end_times;

  for (int i = 0; i < Q; i++) {
    int start, end, x;
    cin >> start >> end >> x;
    start--;
    end--;
    queries.emplace_back(i, x);
    start_times.emplace(start, i);
    end_times.emplace(end, i);
  }

  vector<int> out_lower, out_upper;
  set<Query> in_bounds;

  DisjointSets ds(Q * 2);

  ll sum = 0;

  for (int i = 0; i < N && !end_times.empty(); i++) {
    sum += deltas[i];

    // Handle start times.
    while (!start_times.empty() && start_times.begin()->first == i) {
      int query_idx = start_times.begin()->second;
      Query& q = queries[query_idx];
      q.offset += deltas[i] - sum;
      in_bounds.emplace(q);
      start_times.erase(start_times.begin());
    }

    // If there are queries that were stuck in the upper bound, and the current
    // number is negative, it means they come back to be in bounds, therefore
    // move them out of the "out_xxx" arrays and into the "in bounds" set.
    // Similarly for queries stuck in the lower bound, they come back to be
    // in bounds when the current number is positive.
    //
    // Since all those queries now have the same value, merge them into one.
    Query new_query(queries.size(), deltas[i] - sum);
    bool merged = false;

    if (deltas[i] < 0 && !out_upper.empty()) {
      new_query.offset += U;
      for (int q_idx : out_upper) ds.merge(q_idx, new_query.idx);
      merged = true;
      out_upper.clear();

    } else if (deltas[i] > 0 && !out_lower.empty()) {
      new_query.offset += L;
      for (int q_idx : out_lower) ds.merge(q_idx, new_query.idx);
      merged = true;
      out_lower.clear();
    }

    // If any "merge" happened, then add the new query (which represents all the
    // merged queries) to the containers.
    if (merged) {
      in_bounds.emplace(new_query);
      queries.push_back(new_query);
    }

    // When queries go below the lower bound, move them out.
    while (!in_bounds.empty() && in_bounds.begin()->get_value(sum) < L) {
      auto it = in_bounds.begin();
      out_lower.push_back(it->idx);
      in_bounds.erase(it);
    }

    // When queries go above the upper bound, move them out.
    while (!in_bounds.empty() && prev(in_bounds.end())->get_value(sum) > U) {
      auto it = prev(in_bounds.end());
      out_upper.push_back(it->idx);
      in_bounds.erase(it);
    }

    // Handle end times.
    while (!end_times.empty() && end_times.begin()->first == i) {
      auto [end_time, query_idx] = *end_times.begin();
      Query& q = queries[ds.find(query_idx)];
      ans[query_idx] = clamp(q.get_value(sum), L, U);
      end_times.erase(end_times.begin());
    }
  }

  for (int i = 0; i < Q; i++) {
    cout << ans[i] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N) solve();
}
