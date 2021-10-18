#include <bits/stdc++.h>

using namespace std;

int H[6], tower1, tower2;

bool decreasing(int a, int b, int c){
  return (a > b) && (b > c);
}

int main(){
  const char* fmt = "%d %d %d %d %d %d\n";
  for(int i=0; i<6; i++)
    cin >> H[i];
  cin >> tower1 >> tower2;

  sort(H, H+6);

  do {
    bool first_height = (H[0] + H[1] + H[2]) == tower1;
    bool second_height = (H[3] + H[4] + H[5]) == tower2;
    bool order1 = decreasing(H[0], H[1], H[2]);
    bool order2 = decreasing(H[3], H[4], H[5]);
    if(first_height && second_height && order1 && order2){
      printf(fmt, H[0], H[1], H[2], H[3], H[4], H[5]);
      break;
    }
  } while(next_permutation(H, H+6));
}
