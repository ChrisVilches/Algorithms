#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int nums[(int)1e5], ans[(int)1e5];

struct DisjointSets {
  DisjointSets(int n) {
    for (int i = 0; i < n; i++) parent.push_back(i);
  }

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
  const int idx, x;
  ll offset;
  Query(int idx, int x) : idx(idx), x(x) {}
  int get_value(ll global_sum) const { return (int)(offset + global_sum); }
  bool operator<(const Query& q) const {
    if (offset != q.offset) return offset < q.offset;
    return idx < q.idx;
  }
};

int N;

void solve() {
  int L, U, Q;
  cin >> L >> U;
  for (int i = 0; i < N; i++) scanf("%d", &nums[i]);

  cin >> Q;

  vector<Query> queries;

  set<pair<int, int>> start_times, end_times;

  for (int i = 0; i < Q; i++) {
    int start, end, x;
    scanf("%d %d %d", &start, &end, &x);
    start--;
    end--;
    queries.push_back(Query(i, x));
    start_times.emplace(make_pair(start, i));
    end_times.emplace(make_pair(end, i));
  }

  vector<int> out_lower, out_upper;
  set<Query> in_bounds;

  DisjointSets ds(Q * 2);

  ll sum = 0;

  for (int i = 0; i < N; i++) {
    if (end_times.empty()) break;
    sum += nums[i];

    // Handle start times.
    while (!start_times.empty() && start_times.begin()->first == i) {
      int query_idx = start_times.begin()->second;
      Query& q = queries[query_idx];
      q.offset = q.x + nums[i] - sum;
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
    Query new_query((int)queries.size(), 0);
    bool merged = false;

    if (nums[i] < 0 && !out_upper.empty()) {
      new_query.offset = U + nums[i] - sum;
      for (int q_idx : out_upper) ds.merge(q_idx, new_query.idx);
      merged = true;
      out_upper.clear();

    } else if (nums[i] > 0 && !out_lower.empty()) {
      new_query.offset = L + nums[i] - sum;
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
      ans[query_idx] = q.get_value(sum);
      end_times.erase(end_times.begin());
    }
  }

  for (int i = 0; i < Q; i++) {
    int value = ans[i];

    if (value >= U)
      printf("%d\n", U);
    else if (value <= L)
      printf("%d\n", L);
    else
      printf("%d\n", value);
  }
}

int main() {
  while (scanf("%d", &N) == 1) solve();
}
