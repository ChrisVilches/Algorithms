#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

int main() {
  ll N;
  cin >> N;

  for (ll i = 0; i < N; i++) {
    if (i > 0) putchar_unlocked(' ');
    cout << fast_fibonacci(i, 1e9 + 7);
  }

  putchar_unlocked('\n');
}
