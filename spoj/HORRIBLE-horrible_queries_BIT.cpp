#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct BIT {
  BIT() {}
  BIT(int n) : bit_n(n + 1) { A.assign(bit_n, 0); }

  void update(int i, ll val) {
    for (; i < bit_n; i += i & -i) A[i] += val;
  }

  ll query(int i) {
    ll ret = 0;
    for (; i > 0; i -= i & -i) ret += A[i];
    return ret;
  }

 private:
  int bit_n;
  vector<ll> A;
};

struct RangeBIT {
  RangeBIT(int n) {
    bit1 = BIT(n);
    bit2 = BIT(n);
  }

  void update_range(int l, int r, ll v) {
    bit1.update(l, v);
    bit1.update(r + 1, -v);
    bit2.update(l, -v * (l - 1));
    bit2.update(r + 1, v * r);
  }

  ll range_sum(int l, int r) {
    ll a = bit1.query(r) * r + bit2.query(r);
    ll b = bit1.query(l - 1) * (l - 1) + bit2.query(l - 1);
    return a - b;
  }

 private:
  BIT bit1, bit2;
};

void solve() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  RangeBIT range_bit(N);

  while (Q--) {
    int is_range_sum_query, p, q;
    ll v;
    scanf("%d %d %d", &is_range_sum_query, &p, &q);

    if (p <= 0) p = 1;  // for uDebug test case.

    // q--;
    // p--;
    if (is_range_sum_query)
      printf("%lld\n", range_bit.range_sum(p, q));
    else {
      scanf("%lld", &v);
      range_bit.update_range(p, q, v);
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) solve();
}
