#include <bits/stdc++.h>
using namespace std;

struct BIT {
  BIT(int n) : bit_n(n + 1) { A.assign(bit_n, 0); }

  void update(int i, int v) {
    i++;
    for (; i < bit_n; i += i & -i) A[i] += v;
  }

  int query(const int l, const int r) { return query(r) - query(l - 1); }

 private:
  int bit_n;
  vector<int> A;
  int query(int i) {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }
};
int main() {
  int n;
  cin >> n;

  vector<tuple<int, int, int>> xs;
  vector<tuple<int, int, int>> ys;

  vector<tuple<int, int, int, int>> segments(n);
  for (auto& s : segments) cin >> get<0>(s) >> get<1>(s) >> get<2>(s) >> get<3>(s);
  vector<tuple<int, int, bool>> all_y;
  for (int i = 0; i < n; i++) {
    all_y.emplace_back(get<1>(segments[i]), i, false);
    all_y.emplace_back(get<3>(segments[i]), i, true);
  }
  sort(all_y.begin(), all_y.end());
  int curr_y = 0;
  for (const auto& [_, idx, is_second] : all_y) {
    if (is_second) {
      get<3>(segments[idx]) = curr_y++;
    } else {
      get<1>(segments[idx]) = curr_y++;
    }
  }

  BIT bit(curr_y);

  for (const auto& [x1, y1, x2, y2] : segments) {
    if (x1 == x2) {
      ys.emplace_back(x1, y1, y2);
    } else {
      xs.emplace_back(x1, y1, 1);
      xs.emplace_back(x2, y1, -1);
    }
  }
  sort(xs.begin(), xs.end());
  sort(ys.begin(), ys.end());

  long long ans = 0;

  auto it = xs.begin();
  for (const auto& [curr_x, y1, y2] : ys) {
    while (it != xs.end()) {
      const auto [x, y, d] = *it;
      if (curr_x < x) break;
      bit.update(y, d);
      it++;
    }
    ans += bit.query(y1, y2);
  }

  cout << ans << endl;
}
