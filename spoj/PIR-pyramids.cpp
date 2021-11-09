#include <bits/stdc++.h>

using namespace std;
typedef long double ld;

// Formula from: https://keisan.casio.com/exec/system/1329962711
// Calculate tetrahedron volume with high accuracy.

void solve(){
  ld a1, a2, a3, a4, a5, a6;

  cin >> a1 >> a2 >> a3 >> a4 >> a6 >> a5;
  a1 *= a1;
  a2 *= a2;
  a3 *= a3;
  a4 *= a4;
  a5 *= a5;
  a6 *= a6;

  ld result = 0;
  ld div = 144.0;
  result += (a1*a5)*(a2+a3+a4+a6-a1-a5)/div;
  result += (a2*a6)*(a1+a3+a4+a5-a2-a6)/div;
  result += (a3*a4)*(a1+a2+a5+a6-a3-a4)/div;
  result += (-(a1*a2*a4)-(a2*a3*a5)-(a1*a3*a6)-(a4*a5*a6))/div;

  result = (ld)sqrt(result);

  printf("%.4Lf\n", result);
}

int main(){
  int T;
  cin >> T;
  while(T--) solve();
}
