#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://oeis.org/A002674

ll MOD = 1e9 + 7;
ll factorial[300001];  // TODO: Should be less??????? I think 2 * n

// TODO: Bullshit implementation. Refactor

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

int main() {
  int t, n;

  factorial[0] = 1;
  factorial[1] = 1;

  for (int i = 2; i < 300001; i++) {
    factorial[i] = i * factorial[i - 1];
    factorial[i] %= MOD;
  }

  cin >> t;

  while (t--) {
    cin >> n;

    cout << mod_divide(factorial[2 * n], 2, MOD) << endl;
  }
}
