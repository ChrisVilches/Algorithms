#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX_N 100'007

const ll mod = 1e9 + 7;
ll nums[MAX_N];
ll tree[4 * MAX_N];

inline ll mult(ll a, ll b) { return (a * b) % mod; }

ll query(int p, int L, int R, int i, int j) {
  if (i > R || j < L) return 1;
  if (i <= L && R <= j) return tree[p];

  int m = (L + R) / 2;
  return mult(query(2 * p, L, m, i, j), query(2 * p + 1, m + 1, R, i, j));
}

void update(int p, int L, int R, int pos, ll new_val) {
  if (L == R) {
    tree[p] = new_val;
  } else {
    int m = (L + R) / 2;
    if (pos <= m)
      update(2 * p, L, m, pos, new_val);
    else
      update(2 * p + 1, m + 1, R, pos, new_val);

    tree[p] = mult(tree[2 * p], tree[2 * p + 1]);
  }
}

void build_tree(int p, int L, int R) {
  if (L == R)
    tree[p] = nums[L];
  else {
    build_tree(2 * p, L, (L + R) / 2);
    build_tree(2 * p + 1, (L + R) / 2 + 1, R);
    tree[p] = mult(tree[2 * p], tree[2 * p + 1]);
  }
}

ll fast_fibonacci(ll n, ll mod) {
  function<pair<ll, ll>(ll)> fib;
  fib = [mod, &fib](ll n) -> pair<ll, ll> {
    if (n == 0) return {0, 1};
    auto [a, b] = fib(n >> 1);
    ll c = 2 * b - a;
    if (c < 0) c += mod;
    c = (a * c) % mod;
    ll d = (a * a + b * b) % mod;
    return n & 1 ? make_pair(d, c + d) : make_pair(c, d);
  };

  return fib(n).first;
}

ll possibilities(ll x) { return fast_fibonacci(x - 1, mod); }

int main() {
  int G, E;
  scanf("%d %d", &G, &E);

  for (int i = 0; i < G; i++) {
    scanf("%lld", &nums[i]);
    nums[i] = possibilities(nums[i]);
  }

  build_tree(1, 0, G - 1);

  while (E--) {
    char type;
    ll a, b;

    scanf(" %c%c %lld %lld", &type, &type, &a, &b);

    bool is_update = type == '-';

    if (is_update)
      update(1, 0, G - 1, (int)a - 1, possibilities(b));
    else
      printf("%lld\n", query(1, 0, G - 1, (int)a - 1, (int)b - 1));
  }

  printf("%lld\n", query(1, 0, G - 1, 0, G - 1));
}
