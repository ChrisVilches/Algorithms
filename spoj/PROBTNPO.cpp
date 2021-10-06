#include <bits/stdc++.h>

using namespace std;

uint x, y;

uint cycle(uint n){
  uint count;
  for(count = 1; n != 1; count++){
    if(n % 2 == 1)
      n = (3 * n) + 1;
    else
      n /= 2;
  }
  return count;
}

void solve(){
  uint max_cycle = 0;
  for(uint i=min(x, y); i<=max(x, y); i++)
    max_cycle = max(max_cycle, cycle(i));

  printf("%u %u %u\n", x, y, max_cycle);
}

int main(){
  while(scanf("%u %u", &x, &y) == 2)
    solve();
}
