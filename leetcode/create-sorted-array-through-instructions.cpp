#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT {
  BIT(const int n) : bit_n(n + 1), A(bit_n, 0) {}

  ll range_sum(const int l, const int r) const { return sum(r) - sum(l - 1); }

  void inc(int i) {
    i++;
    for (; i < bit_n; i += i & -i) A[i]++;
  }

 private:
  const int bit_n;
  vector<ll> A;

  ll sum(int i) const {
    i++;
    ll sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }
};

class Solution {
  const ll mod = 1e9 + 7;
  const int max_n = 100'007;

 public:
  int createSortedArray(const vector<int>& instructions) {
    BIT bit(max_n);

    ll ans = 0;

    for (const int x : instructions) {
      const ll lhs = bit.range_sum(0, x - 1);
      const ll rhs = bit.range_sum(x + 1, max_n - 1);

      ans += min(lhs, rhs);
      ans %= mod;

      bit.inc(x);
    }

    return ans;
  }
};
