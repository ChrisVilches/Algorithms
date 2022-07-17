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

int ans[300'001];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, L;
  cin >> N >> M >> L;

  vector<tuple<int, int, int, int>> sides;

  for (int i = 0; i < N; i++) {
    int x, y, X, Y;
    cin >> x >> y >> X >> Y;

    sides.push_back({(x * 2) - 1, y, Y, 1});
    sides.push_back({(X * 2) + 1, y, Y, -1});
  }

  priority_queue<tiii, vector<tiii>, greater<tiii>> queries;

  for (int i = 0; i < M; i++) {
    int x, y;
    cin >> x >> y;
    queries.push({x * 2, y, i});
  }

  BIT bit(5007);

  sort(sides.begin(), sides.end());

  for (const auto& [x, y1, y2, d] : sides) {
    while (!queries.empty() && get<0>(queries.top()) < x) {
      const auto [_, y, idx] = queries.top();
      ans[idx] = bit.query(y);
      queries.pop();
    }

    bit.range_update(y1, y2, d);
  }

  for (int i = 0; i < M; i++) {
    cout << ans[i] << endl;
  }
}
