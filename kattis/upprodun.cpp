#include <bits/stdc++.h>

using namespace std;

int main(){
  int teams, rooms;
  cin >> rooms >> teams;

  int div = teams / rooms;
  int rem = teams % rooms;

  for(int i=0; i<rooms; i++){
    if(rem-- > 0){
      cout << "*";
    }
    for(int j=0; j<div; j++){
      cout << "*";
    }
    cout << endl;
  }
}
