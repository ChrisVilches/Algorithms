#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll N;

map<ll, ll> memo;

ll dp(ll n) {
  if (n == 0) return 0;
  if (memo.count(n)) return memo[n];

  ll exchanged = dp(n / 2) + dp(n / 3) + dp(n / 4);
  ll not_exchanged = n;

  return memo[n] = max(exchanged, not_exchanged);
}

int main() {
  while (scanf("%lld", &N) == 1) {
    memo.clear();
    cout << dp(N) << endl;
  }
}
