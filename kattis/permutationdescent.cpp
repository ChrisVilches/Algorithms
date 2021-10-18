#include <bits/stdc++.h>

using namespace std;

/*
* First use brute force to find sequence (e.g. I used C++'s next_permutation to aid myself),
* then find the formula. In this case, the formula was exactly the same as Euler Triangle,
* (sequence A008292 in the OEIS).
*/

#define MOD 1001113
int memo[1000][1000];

int pdc(int n, int v){
  if(n < 0 || v < 0) return 0;
  if(n == 0 && v == 0) return 1;
  if(memo[n][v] != -1) return memo[n][v];
  int x = (n - v) * pdc(n - 1, v - 1);
  int y = (v + 1) * pdc(n - 1, v);
  int ret = ((x % MOD) + (y % MOD)) % MOD;
  return memo[n][v] = ret;
}

void solve(){
  memset(memo, -1, sizeof memo);
  int K, N, v;
  cin >> K >> N >> v;
  printf("%d %d\n", K, pdc(N, v));
}

int main(){
  int t;
  cin >> t;
  while(t--) solve();
}
