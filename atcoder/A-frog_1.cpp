#include <bits/stdc++.h>
using namespace std;

int N, A[100001];
int memo[100001];

int dp(int i) {
  if (i == N - 1) return 0;
  if (~memo[i]) return memo[i];

  int one = abs(A[i] - A[i + 1]) + dp(i + 1);
  if (i == N - 2) return one;

  int two = abs(A[i] - A[i + 2]) + dp(i + 2);

  return memo[i] = min(one, two);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  memset(memo, -1, sizeof memo);

  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  cout << dp(0) << endl;
}
