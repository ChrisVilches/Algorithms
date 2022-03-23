#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tiii;

struct tiii_hash {
  uint32_t operator()(const tiii& t) const {
    const auto [a, b, c] = t;
    return a ^ b ^ c;
  }
};

int N, K, nums[40];
unordered_map<tiii, int, tiii_hash> memo;

int dp(const int i, const int curr, const int k) {
  if (i == N) return k == 0 ? curr : 0;
  if (memo.count({i, curr, k})) return memo[{i, curr, k}];

  int take = dp(i + 1, nums[i] & curr, k - 1);
  int skip = dp(i + 1, curr, k);

  return memo[{i, curr, k}] = max(take, skip);
}

void solve() {
  memo.clear();
  cin >> N >> K;

  for (int i = 0; i < N; i++) {
    cin >> nums[i];
  }

  cout << dp(0, -1, K) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  while (T--) solve();
}
