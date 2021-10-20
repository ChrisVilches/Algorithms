
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

int MOD = 1000000007;

ll memo[5001][5001];
ll memo2[5001][5001];

ll dp(int s, int b) {
  if (s == 0 || b == 0) return 0;
  if (s > b) return 0;
  if (s == 1 || b == 1 || b == s) return 1;
  if (memo[s][b] != -1) return memo[s][b];

  ll sum;
  sum = 0;
  sum = (sum + dp(s, b - s)) % MOD;
  sum = (sum + dp(s - 1, b - 1)) % MOD;
  sum = (sum + dp(s - 1, b - 1)) % MOD;
  sum = (sum - dp(s - 2, b - 2)) % MOD;
  memo[s][b] = sum % MOD;
  return memo[s][b];
}

ll dp2(int s, int b) {
  if (s == 0 || b == 0) return 0;
  if (s > b) return 0;
  if (s == 1 || b == 1 || b == s) return 1;
  if(memo2[s][b] != -1) return memo2[s][b];

  ll sum = 0;
  for (int i = 0; i < min(s, b); i++) {
    sum += (i + 1) * dp(s - i, b - s);
    sum = sum % MOD;
  }

  return memo2[s][b] = (int)(sum % MOD);
}

int main() {
  int S, B;
  /*
  memset(memo, -1, sizeof memo);
 for(int i=0; i<20; i++){
   for(int j=0; j<20; j++){
     cout << dp(i, j) << " ";
   }
   cout << endl;
 }*/
 for(int i=0; i<5001; i++){
   for(int j=0; j<5001; j++){
     memo[i][j] = -1;
     memo2[i][j] = -1;
   }
 }
  // memset(memo, -1, sizeof memo);
  //memset(memo2, -1, sizeof memo2);
  while (scanf("%d %d", &S, &B) == 2) {
    // fprintf(stderr, "S=%d B=%d\n", S, B);
    printf("%d\n", dp2(S, B));
  }
}
