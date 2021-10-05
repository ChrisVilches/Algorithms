#include <bits/stdc++.h>

using namespace std;

// Fast Exponentiation

typedef long long ll;
ll mod = 1000000007;

int cases, m, n;
ll mat[55][55];
ll result[55][55];
ll temp[55][55];

void mult(ll (&a)[55][55], ll (&b)[55][55]){
  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      ll sum = 0;
      for(int x=0; x<m; x++){
        ll mult = (b[i][x] * a[x][j]) % mod;
        sum = (sum + mult) % mod;
      }
      temp[i][j] = sum;
    }
  }

  memcpy(a, temp, 55 * 55);
}

void solve(){
  cin >> m >> n;

  for(int i=0; i<m; i++)
    for(int j=0; j<m; j++)
      cin >> mat[i][j];

  memcpy(result, mat, 55 * 55);

  n--; // When n=1 the matrix remains the same.

  for(; n; n >>= 1){
    if(n & 1)
      mult(result, mat);
    mult(mat, mat);
  }

  for(int i=0; i<m; i++)
    for(int j=0; j<m; j++)
      printf("%lld ", result[i][j]);
    printf("\n");
}

int main(){
  cin >> cases;
  while(cases--) solve();
}
