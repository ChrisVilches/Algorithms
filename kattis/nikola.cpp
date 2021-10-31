#include <bits/stdc++.h>

using namespace std;

int fee[1001];
int N;
int memo[1001][1001];

int dp(int square, int jump) {
  if (square >= N) return INT_MAX;
  if (square < 0) return INT_MAX;
  if (square == N - 1) return fee[square];
  if (memo[square][jump] != -1) return memo[square][jump];

  int forward = dp(square + jump + 1, jump + 1);
  int backward = dp(square - jump, jump);

  return memo[square][jump] = fee[square] + min(forward, backward);
}

int main() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> fee[i];
  memset(memo, -1, sizeof memo);

  cout << dp(1, 1) << endl;
}
