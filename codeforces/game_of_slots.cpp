#include <bits/stdc++.h>
using namespace std;

double memo[101][101][101];
bool ok[101][101][101];

double dp(const int a, const int b, int k) {
  if (a == 0 && b == 0) return 0;
  if (a < 0 || b < 0) return 0;
  k = max(k, 0);
  if (ok[a][b][k]) return memo[a][b][k];

  const double p = static_cast<double>(a) / (a + b);
  const double score = k == 0 ? a : 0;

  const double win = p * (score + dp(a - 1, b, k - 1));
  const double lose = (1 - p) * dp(a, b - 1, k + 1);

  ok[a][b][k] = true;
  return memo[a][b][k] = win + lose;
}

int main() {
  int n;
  memset(ok, 0, sizeof ok);

  while (cin >> n) {
    cout << fixed << setprecision(6) << dp(n, n, 0) << endl;
  }
}
