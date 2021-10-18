#include <bits/stdc++.h>

using namespace std;

int main(){
  int a, b;
  while(scanf("%d %d", &a, &b) == 2){
    if((a | b) == 0) break;
    if(a + b == 13){
      cout << "Never speak again." << endl;
      continue;
    } else if(a > b){
      cout << "To the convention." << endl;
    } else if(a < b){
      cout << "Left beehind." << endl;
    } else {
      cout << "Undecided." << endl;
    }
  }
}
