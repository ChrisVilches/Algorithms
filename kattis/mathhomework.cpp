#include <bits/stdc++.h>

using namespace std;

#define MEMO_SIZE 251

int b, d, c, l;

bool found = false;
short memo[MEMO_SIZE][MEMO_SIZE][MEMO_SIZE];

void count(int first, int second, int third){
  if(memo[first][second][third] != -1)
    return;

  int total_legs = (first*b) + (second*d) + (third*c);
  if(total_legs == l){
    found = true;
    memo[first][second][third] = 1;
    return;
  }

  memo[first][second][third] = 0;

  if(total_legs > l)
    return;

  for(int i=0; i<(1<<3); i++){
    int b1 = (i&1) > 0;
    int b2 = (i&(1<<1)) > 0;
    int b3 = (i&(1<<2)) > 0;
    count(first+b1, second+b2, third+b3);
  }
}

int main(){
  cin >> b >> d >> c >> l;
  for(int i=0; i<MEMO_SIZE; i++)
    for(int j=0; j<MEMO_SIZE; j++)
      for(int k=0; k<MEMO_SIZE; k++)
        memo[i][j][k] = -1; // memset doesn't work for 3D arrays

  count(0, 0, 0);

  for(int i=0; i<MEMO_SIZE; i++)
    for(int j=0; j<MEMO_SIZE; j++)
      for(int k=0; k<MEMO_SIZE; k++)
        if(memo[i][j][k] == 1)
          printf("%d %d %d\n", i, j, k);

  if(!found)
    cout << "impossible" << endl;
}
