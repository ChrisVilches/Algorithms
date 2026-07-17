#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;
  const ll mod = 1e9 + 7;

  ll fast_exponentiation(const ll a, const ll n) {
    if (n == 0) return 1;

    if (n & 1) {
      return (a * fast_exponentiation(a, n - 1)) % mod;
    }

    return fast_exponentiation((a * a) % mod, n / 2) % mod;
  }

 public:
  int monkeyMove(int n) {
    const ll res = fast_exponentiation(2, n);
    return (res + mod - 2) % mod;
  }
};
