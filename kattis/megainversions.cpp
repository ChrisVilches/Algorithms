#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

int main() {
  int n;
  while (cin >> n) {
    vector<int> nums(n);
    for (auto& x : nums) cin >> x;

    set<pair<int, int>> order;

    for (int i = 0; i < n; i++) {
      order.emplace(nums[i], i);
    }

    BIT less_than(n), visited(n);

    ll ans = 0;

    for (const auto& [_, idx] : order) {
      ans += less_than.range_sum(idx, n - 1);

      less_than.update(idx, visited.range_sum(idx, n - 1));
      visited.update(idx, 1);
    }

    cout << ans << endl;
  }
}
