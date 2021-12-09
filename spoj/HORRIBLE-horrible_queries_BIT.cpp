#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct BIT {
  BIT() {}
  BIT(int n) : bit_n(n + 1) { A.assign(bit_n, 0); }

  ll query(int i) {
    i++;
    ll sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

  void update(int i, ll v) {
    i++;
    for (; i <= bit_n; i += i & -i) A[i] += v;
  }

 private:
  int bit_n;
  vector<ll> A;
};

struct RangeBIT {
  RangeBIT(int n) {
    bit1 = BIT(n + 2);
    bit2 = BIT(n + 2);
  }

  void update_range(int i, int j, ll v) {
    i++;
    j++;
    bit1.update(i, v);
    bit1.update(j + 1, -v);
    bit2.update(i, v * (i - 1));
    bit2.update(j + 1, -v * j);
  }

  ll range_sum(int i, int j) {
    i++;
    j++;
    ll a = (bit1.query(j) * j) - bit2.query(j);
    ll b = (bit1.query(i - 1) * (i - 1)) - bit2.query(i - 1);
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
    p--;
    q--;

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
