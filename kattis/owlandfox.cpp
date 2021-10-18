#include <bits/stdc++.h>

using namespace std;

void solve(){
  string digits;
  cin >> digits;

  for(int i=digits.size()-1; i>=0; i--){
    if(digits[i] > '0'){
      digits[i]--;
      break;
    }
  }

  for(int i=0; i<digits.size(); i++){
    if(digits[i] != '0'){
      cout << digits << endl;
      return;
    }
  }
  cout << 0 << endl;
}

int main(){
  int t;
  cin >> t;
  while(t--) solve();
}
