#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://oeis.org/A003435

const ll MOD = 1e9 + 7;
ll memo[100001];

ll gcd_extended(ll a, ll b, ll& x, ll& y) {
  if (a == 0) {
    x = 0, y = 1;
    return b;
  }

  ll x1, y1;
  ll gcd = gcd_extended(b % a, a, x1, y1);

  x = y1 - (b / a) * x1;
  y = x1;

  return gcd;
}

ll mod_inverse(ll b, ll m) {
  ll x, y;
  ll g = gcd_extended(b, m, x, y);
  if (g != 1) return -1;
  return (x % m + m) % m;
}

ll mod_divide(ll a, ll b, ll m) {
  a = a % m;
  ll inv = mod_inverse(b, m);
  assert(~inv);
  return (inv * a) % m;
}

ll mult(const initializer_list<ll>& args) {
  ll res = 1;

  for (const ll val : args) {
    res = (res * val) % MOD;
  }
  return res;
}

ll dp(const ll n) {
  if (n == 1) return 0;
  if (n == 2) return 8;
  if (n == 3) return 192;
  if (~memo[n]) return memo[n];

  ll a = mult({2, n, (4 * n * n) - (8 * n) + 5, dp(n - 1)});
  ll b = mult({4, n - 1, n, 2 * n - 1, dp(n - 2)});

  return memo[n] = mod_divide(a + b, 2 * n - 3, MOD);
}

int main() {
  int T, n;
  cin >> T;

  memset(memo, -1, sizeof memo);

  while (T--) {
    cin >> n;
    cout << dp(n) << endl;
  }
}
