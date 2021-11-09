#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

int MOD = 1e9 + 7;
int memo[5001][5001];

ll dp(int s, int b) {
  if (s == 0 || b == 0) return 0;
  if (s > b) return 0;
  if (s == 1 || b == 1 || b == s) return 1;
  if (memo[s][b] != -1) return memo[s][b];
  ll result = dp(s, b - s) + 2 * dp(s - 1, b - 1) - dp(s - 2, b - 2);
  return memo[s][b] = result % MOD;
}

int calculate(int s, int b) {
  if (s == 1 || b == 1 || b == s) return 1;
  ll sum = 0;
  for (int i = 0; i < min(s, b); i++) {
    sum += (i + 1) * dp(s - i, b - s);
    sum = sum % MOD;
  }
  return (int)sum;
}

int main() {
  int S, B;
  memset(memo, -1, sizeof memo);

  while (scanf("%d %d", &S, &B) == 2) {
    printf("%d\n", calculate(S, B));
  }
}
