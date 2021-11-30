#include <bits/stdc++.h>

using namespace std;

double memo[2000][2000];

double p(int n, int k) {
  if (n >= 2000 || k >= 2000) return 0;
  if (n == 0 && k != 0) return 0;
  if (n == 0 && k == 0) return 1;
  if (k < 0) return 0;
  if (memo[n][k] > -1) return memo[n][k];

  double res = 0;

  res += p(n - 1, k - 1);
  res += p(n - 1, k - 2);
  res += p(n - 1, k - 3);
  res += p(n - 1, k - 4);
  res += p(n - 1, k - 5);
  res += p(n - 1, k - 6);

  res /= 6;

  return memo[n][k] = res;
}

void solve() {
  int N, K;
  cin >> N >> K;
  cout << floor(p(N, K) * 100) << endl;
}

int main() {
  memset(memo, -1, sizeof memo);
  int T;
  cin >> T;
  while (T--) solve();
}
