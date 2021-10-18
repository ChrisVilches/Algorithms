#include <bits/stdc++.h>

using namespace std;

int plates[1001][1001];
int memo[1001][2001];
int N, K, P;

int knapsack(int n, int p){
  if(p == 0) return 0;
  if(n < 0) return 0;
  if(memo[n][p] != -1) return memo[n][p];

  int val = knapsack(n - 1, p);

  int accum = 0;
  int rem_plates = p;
  for(int i=0; i<K; i++){
    accum += plates[n][i];

    if(rem_plates > 0){
      rem_plates--;
      val = max(val, accum + knapsack(n - 1, rem_plates));
    } else {
      break;
    }
  }
  return memo[n][p] = val;
}

void solve(){
  memset(memo, -1, sizeof memo);
  cin >> N >> K >> P;
  for(int i=0; i<N; i++)
    for(int j=0; j<K; j++)
      cin >> plates[i][j];

  cout << knapsack(N - 1, P) << endl;
}

int main(){
  int t;
  cin >> t;
  for(int i=0; i<t; i++){
    printf("Case #%d: ", i+1);
    solve();
  }
  return 0;
}
