
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

ll MOD = 1e9 + 7;

ll memo[5001][5001];
ll memo2[5001][5001];
int S, B;

ll dp(int s, int b) {
  if(s < 0 || b < 0) return 0;
  if(s == 0 || b == 0) return 0;
  if(s > b) return 0;
  if(s == 1 || b == 1 || b == s) return 1;
  if(memo[s][b] != -1) return (memo[s][b] % MOD);
  //int  sum = ((dp(s, b-s) % MOD + ((2*dp(s-1, b-1)%MOD)%MOD)%MOD) - dp(s-2, b-2)%MOD) % MOD;

  ll sum;
  sum = 0;
  sum = (sum + dp(s, b-s)) % MOD;
  sum = (sum + dp(s-1, b-1)) % MOD;
  sum = (sum - dp(s-2, b-2)) % MOD;
  sum = (sum + dp(s-1, b-1)) % MOD;
  return memo[s][b] = (sum % MOD);
}

ll dp2(int s, int b){
  if(s == 0 || b == 0) return 0;
  if(s > b) return 0;
  if(s == 1 || b == 1 || b == s) return 1;

  ll sum = 0;
  for(int i=0; i<min(s, b); i++){
    sum += (i + 1) * dp(s-i, b-s);
    sum = sum % MOD;
  }

  return sum;
}

int main() {/*
  memset(memo, -1, sizeof memo);
 for(int i=0; i<20; i++){
   for(int j=0; j<20; j++){
     cout << dp(i, j) << " ";
   }
   cout << endl;
 }*/
  memset(memo, -1, sizeof memo);
  //memset(memo2, -1, sizeof memo2);
  while (scanf("%d %d", &S, &B) == 2) {
    //fprintf(stderr, "S=%d B=%d\n", S, B);
    printf("%lld\n", dp(S, B));
  }
}
