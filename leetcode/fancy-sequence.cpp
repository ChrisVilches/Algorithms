#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 1e9 + 7;

tuple<ll, ll, ll> gcd_extended(const ll a, const ll b) {
  if (a == 0) return {b, 0, 1};

  const auto [g, x1, y1] = gcd_extended(b % a, a);
  return {g, y1 - (b / a) * x1, x1};
}

ll mod_inverse(const ll a, const ll m) {
  const auto [g, x, _] = gcd_extended(a, m);
  return g == 1 ? (x % m + m) % m : -1;
}

ll mod_divide(const ll a, const ll b, const ll m) {
  const ll inv = mod_inverse(b, m);
  assert(inv != -1);
  return inv * (a % m) % m;
}

struct AffineTransformation {
  ll scale, translation;
};

class Fancy {
  vector<int> nums;
  vector<AffineTransformation> frozen;
  AffineTransformation global{1, 0};

 public:
  void append(const int val) {
    nums.emplace_back(val);
    frozen.emplace_back(global);
  }

  void addAll(const int inc) {
    global.translation += inc;
    global.translation %= mod;
  }

  void multAll(const int m) {
    global.scale *= m;
    global.translation *= m;
    global.scale %= mod;
    global.translation %= mod;
  }

  int getIndex(const int idx) {
    if (static_cast<size_t>(idx) >= nums.size()) return -1;

    const auto [a1, b1] = frozen[idx];
    const auto [a2, b2] = global;
    const int x = nums[idx];

    return (mod_divide(x * a2, a1, mod) + b2 - mod_divide(a2 * b1, a1, mod) + mod) % mod;
  }
};
