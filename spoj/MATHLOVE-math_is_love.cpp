#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll sum(const ll n) { return n * (n + 1) / 2; }

ll calculate(const ll y) {
  ll lo = 0;
  ll hi = 3'000'000'000;

  while (lo < hi) {
    const ll mid = (lo + hi) / 2;
    if (sum(mid) == y) {
      return mid;
    }

    if (sum(mid) < y) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }

  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  while (T--) {
    ll Y;
    cin >> Y;

    const ll result = calculate(Y);

    if (result == -1) {
      cout << "NAI" << '\n';
    } else {
      cout << result << '\n';
    }
  }
}
