#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll memo[40];

ll dp(int n){
  if(n % 2 == 1) return 0;
  if(n == 0) return 1;
  if(n == 2) return 3;
  if(memo[n] != -1) return memo[n];
  return memo[n] = 4 * dp(n - 2) - dp(n - 4);
}

int main(){
  int n;
  while(scanf("%d", &n) == 1){
    memset(memo, -1, sizeof memo);
    if(n == -1) break;
    cout << dp(n) << endl;
  }
}
