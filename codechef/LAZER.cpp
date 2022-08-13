#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tiii;

struct BIT {
  BIT(int n) : bit_n(n + 1) { A.assign(bit_n, 0); }

  void range_update(int i, int j, int v) {
    update(i, v);
    update(j + 1, -v);
  }

  int query(int i) {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

 private:
  int bit_n;
  vector<int> A;
  void update(int i, int v) {
    i++;
    for (; i < bit_n; i += i & -i) A[i] += v;
  }
};

int compress(vector<tiii>& queries, vector<int>& A) {
  vector<tiii> all_y;

  for (int i = 0; i < (int)queries.size(); i++) {
    all_y.emplace_back(get<2>(queries[i]), true, i);
  }

  for (int i = 0; i < (int)A.size(); i++) {
    all_y.emplace_back(A[i], false, i);
  }

  sort(all_y.begin(), all_y.end());

  int curr = get<0>(all_y.front());
  int val = 0;

  for (const auto& [y, is_query, idx] : all_y) {
    if (y != curr) val++;
    curr = y;

    if (is_query) {
      get<2>(queries[idx]) = val;
    } else {
      A[idx] = val;
    }
  }

  return val;
}

void solve() {
  int N, Q;
  cin >> N >> Q;

  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  vector<tiii> queries(Q);
  for (auto& q : queries) cin >> get<0>(q) >> get<1>(q) >> get<2>(q);
  for (auto& q : queries) get<0>(q)--, get<1>(q)--;

  const int compressed_size = compress(queries, A) + 1;

  priority_queue<tiii, vector<tiii>, greater<tiii>> enter, exit;

  for (int i = 0; i < Q; i++) {
    const auto [x1, x2, y] = queries[i];
    enter.emplace(x1, y, i);
    exit.emplace(x2, y, i);
  }

  vector<int> ans(Q);

  BIT bit(compressed_size);

  for (int x = 1; x <= N; x++) {
    while (!enter.empty() && get<0>(enter.top()) < x) {
      const auto [_, y, idx] = enter.top();
      ans[idx] = bit.query(y);
      enter.pop();
    }

    if (x < N) {
      const auto [from, to] = minmax(A[x - 1], A[x]);
      bit.range_update(from, to, 1);
    }

    while (!exit.empty() && get<0>(exit.top()) <= x) {
      const auto [_, y, idx] = exit.top();
      ans[idx] = bit.query(y) - ans[idx];
      exit.pop();
    }
  }

  for (const int a : ans) {
    cout << a << '\n';
  }
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
