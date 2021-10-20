
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll MOD = 1e9 + 7;

ll memo[5001][5001];
int S, B;

ll dp(int s, int b) {
  if(s < 0 || b < 0) return 0;
  if(s == 0 || b == 0) return 0;
  if(s > b) return 0;
  if(s == 1 || b == 1 || b == s) return 1;
  if(memo[s][b] != -1) return memo[s][b];
  ll sum = ((dp(s, b-s) + ((2*dp(s-1, b-1)))) - dp(s-2, b-2)%MOD) % MOD;
  return memo[s][b] = sum;
}

int main() {
  memset(memo, -1, sizeof memo);
 for(int i=0; i<20; i++){
   for(int j=0; j<20; j++){
     cout << dp(i, j) << " ";
   }
   cout << endl;
 }
  while (scanf("%d %d", &S, &B) == 2) {
    memset(memo, -1, sizeof memo);
    printf("%lld\n", dp(S, B) % MOD);
  }
}
