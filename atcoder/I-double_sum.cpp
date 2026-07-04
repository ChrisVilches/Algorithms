#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT {
  BIT(const int n) : bit_n(n + 1), A(bit_n, 0) {}

  ll range_sum(const int l, const int r) const { return sum(r) - sum(l - 1); }

  void update(int i, const ll v) {
    i++;
    for (; i < bit_n; i += i & -i) A[i] += v;
  }

 private:
  ll sum(int i) const {
    i++;
    ll sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

  const int bit_n;
  vector<ll> A;
};

int main() {
  int n;
  while (cin >> n) {
    vector<ll> nums(n);
    for (ll& x : nums) cin >> x;

    const set<ll> ordered_unique{nums.begin(), nums.end()};

    unordered_map<ll, int> idx_map;

    for (const ll x : ordered_unique) {
      idx_map[x] = idx_map.size();
    }

    const int bit_size = idx_map.size();

    BIT bit(bit_size);
    BIT counts(bit_size);

    for (const ll x : nums) {
      const int idx = idx_map[x];
      bit.update(idx, x);
      counts.update(idx, 1);
    }

    ll ans = 0;

    for (const ll x : nums) {
      const int idx = idx_map[x];
      const ll count = counts.range_sum(idx + 1, bit_size - 1);
      const ll val = bit.range_sum(idx + 1, bit_size - 1);

      ans += val - (x * count);

      bit.update(idx, -x);
      counts.update(idx, -1);
    }

    cout << ans << endl;
  }
}
