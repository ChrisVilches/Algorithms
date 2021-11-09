#include <bits/stdc++.h>

using namespace std;

int necessary[6] = {1, 1, 2, 2, 2, 8};

int main(){
  int n;

  for(int i=0; i<6; i++){
    cin >> n;
    cout << necessary[i] - n << " ";
  }
  cout << endl;
}
