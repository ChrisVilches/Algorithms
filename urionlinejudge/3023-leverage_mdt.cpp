#include <bits/stdc++.h>

using namespace std;

int mat[1001][1001];
int memo[1001][1001];
int N, M;

int dp(int n, int m){
  if(n == 0) return 1;
  if(m == 0) return 1;
  if(memo[n][m] != -1) return memo[n][m];

  if(mat[n][m] == mat[n][m-1] && mat[n-1][m] == mat[n-1][m-1])
    return memo[n][m] = 1 + min({ dp(n-1, m-1), dp(n-1, m), dp(n, m-1) });

  return memo[n][m] = 1;
}

void solve(){
  for(int i=0; i<N; i++){
    string row;
    cin >> row;
    for(int j=0; j<M; j++)
      mat[i][j] = row[j] == 'G';
  }

  int side = 0;

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      side = max(side, dp(i, j));

  cout << side * side << endl;
}

int main(){
  while(scanf("%d %d", &N, &M) == 2){
    memset(memo, -1, sizeof memo);
    solve();
  }
}
