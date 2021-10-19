#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll MOD = 1e9 + 7;

int memo[5001][5001];

int S, B;

int dp(int s, int b){
  //printf("DP(%d, %d)\n", s, b);
  if(s < 0 || b < 0) return 0;
  if(s == 0 || b == 0) return 0;
  if(s > b) return 0;
  if(s == 1) return 1;
  if(b == 1) return 1;
  if(b == s) return 1;
  if(memo[s][b] != -1) return memo[s][b];

  ll sum = 0;
  for(int i=0; i<min(s, b); i++){
    ll factor = i + 1;
    //printf("%lld x ", factor);
    sum += (factor * dp(s-i, b-s)) % MOD;
  }

  return memo[s][b] = (sum % MOD);
}

void solve(){
  memset(memo, -1, sizeof memo);
  cout << dp(S, B) << endl;

  for(int i=0; i<30; i++){
    for(int j=0; j<30; j++){
      cout << memo[i][j] << " ";
    }
    cout << endl;
  }
}

int main(){
  while(scanf("%d %d", &S, &B) == 2){
    solve();
  }
}
