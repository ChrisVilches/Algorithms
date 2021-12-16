#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
ll nums[100'007];

struct Segtree {
  Segtree(ll* arr, int n) {
    tree.assign(4 * n, 1);
    build(arr, 1, 0, n - 1);
  }

  ll query(int p, int L, int R, int i, int j) {
    if (i > R || j < L) return 1;
    if (i <= L && R <= j) return tree[p];

    return mult(query(left(p), L, (L + R) / 2, i, j),
                query(right(p), (L + R) / 2 + 1, R, i, j));
  }

  void update(int p, int L, int R, int pos, ll new_val) {
    if (L == R) {
      tree[p] = new_val;
    } else {
      int m = (L + R) / 2;
      if (pos <= m)
        update(left(p), L, m, pos, new_val);
      else
        update(right(p), m + 1, R, pos, new_val);

      tree[p] = mult(tree[left(p)], tree[right(p)]);
    }
  }

 private:
  vector<ll> tree;
  inline int left(int p) { return p << 1; }
  inline int right(int p) { return (p << 1) + 1; }
  inline ll mult(int a, int b) { return ((ll)a * (ll)b) % mod; }

  void build(ll* A, int p, int L, int R) {
    if (L == R)
      tree[p] = A[L];
    else {
      build(A, left(p), L, (L + R) / 2);
      build(A, right(p), (L + R) / 2 + 1, R);
      tree[p] = mult(tree[left(p)], tree[right(p)]);
    }
  }
};

struct FastFibonacci {
  ll get(ll n, ll mod) {
    fast_fib(n, mod);
    return ans[0];
  }

 private:
  ll a, b, c, d, ans[2];
  void fast_fib(ll n, ll mod) {
    if (n == 0) {
      ans[0] = 0, ans[1] = 1;
      return;
    }
    fast_fib(n >> 1, mod);
    a = ans[0], b = ans[1], c = 2 * b - a;
    if (c < 0) c += mod;
    c = (a * c) % mod;
    d = (a * a + b * b) % mod;
    if (n & 1) {
      ans[0] = d;
      ans[1] = c + d;
    } else {
      ans[0] = c;
      ans[1] = d;
    }
  }
};

ll possibilities(ll x) { return FastFibonacci().get(x - 1, mod); }

int main() {
  int G, E;
  scanf("%d %d", &G, &E);

  for (int i = 0; i < G; i++) {
    scanf("%lld", &nums[i]);
    nums[i] = possibilities(nums[i]);
  }

  Segtree st(nums, G);

  while (E--) {
    char type;
    ll a, b;

    scanf(" %c%c %lld %lld", &type, &type, &a, &b);

    bool is_update = type == '-';

    if (is_update)
      st.update(1, 0, G - 1, (int)a - 1, possibilities(b));
    else
      printf("%lld\n", st.query(1, 0, G - 1, (int)a - 1, (int)b - 1));
  }

  printf("%lld\n", st.query(1, 0, G - 1, 0, G - 1));
}
