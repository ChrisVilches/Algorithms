#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

template <class T>
struct BIT {
  BIT(int n) : bit_n(n + 1) { A.assign(bit_n, 0); }

  T query(int i) const {
    i++;
    T sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

  void update(int i, T v) {
    i++;
    for (; i < bit_n; i += i & -i) A[i] += v;
  }

 private:
  const int bit_n;
  vector<T> A;
};

template <class T>
struct RangeBIT {
  RangeBIT(int n) : bit1(BIT<T>(n)), bit2(BIT<T>(n)) {}

  void update_range(int l, int r, T v) {
    bit1.update(l, v);
    bit1.update(r + 1, -v);
    bit2.update(l, -v * (l - 1));
    bit2.update(r + 1, v * r);
  }

  T range_sum(int l, int r) const {
    T a = bit1.query(r) * r + bit2.query(r);
    T b = bit1.query(l - 1) * (l - 1) + bit2.query(l - 1);
    return a - b;
  }

 private:
  BIT<T> bit1, bit2;
};

struct Query {
  char type;
  int arg1, arg2;

  static Query from_stdin() {
    Query q;
    cin >> q.type >> q.arg1;
    if (q.type != 'R') cin >> q.arg2;
    return q;
  }
};

vector<int> initial_values;
vector<Query> queries;
vector<pii> all_values;
map<pii, vector<pii>> after;
map<int, priority_queue<pii, vector<pii>, greater<pii>>> positions;

void read_initial_values() {
  int N;
  cin >> N;
  initial_values = vector<int>(N);
  for (int i = 0; i < N; i++) cin >> initial_values[i];
}

void read_queries() {
  int Q;
  cin >> Q;
  queries = vector<Query>(Q);
  for (int i = 0; i < Q; i++) queries[i] = Query::from_stdin();
}

void add_values(const int occurrence, const int enemy) {
  all_values.push_back({occurrence, enemy});

  const vector<pii>& after_values = after[{occurrence, enemy}];

  for (auto it = after_values.rbegin(); it != after_values.rend(); it++)
    add_values(it->first, it->second);
}

void set_positions() {
  map<int, int> occurrences;

  for (int init : initial_values) occurrences[init] = 1;

  for (const auto& [type, p, e] : queries)
    if (type == 'I') after[{occurrences[e], e}].push_back({++occurrences[p], p});

  for (int init : initial_values) add_values(1, init);

  for (int i = 0; i < (int)all_values.size(); i++) {
    const auto [occurrence, enemy] = all_values[i];
    positions[enemy].push({occurrence, i});
  }
}

void execute_query(const Query& q, RangeBIT<int>& bit) {
  int pos1, pos2;
  pos1 = positions[q.arg1].top().second;

  switch (q.type) {
    case 'I':
      bit.update_range(pos1, pos1, 1);
      break;
    case 'R':
      positions[q.arg1].pop();
      bit.update_range(pos1, pos1, -1);
      break;
    case 'Q':
      pos2 = positions[q.arg2].top().second;
      if (pos1 > pos2) swap(pos1, pos2);

      cout << bit.range_sum(pos1, pos2) - 2 << '\n';
      break;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  read_initial_values();
  read_queries();
  set_positions();

  RangeBIT<int> bit(all_values.size());

  for (const int init_val : initial_values) {
    auto [_, pos] = positions[init_val].top();
    bit.update_range(pos, pos, 1);
  }

  for (const Query& q : queries) execute_query(q, bit);
}
