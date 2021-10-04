#include <bits/stdc++.h>

using namespace std;

void solve(){
  int k;
  cin >> k;
  int sum = 0;

  for(int i=0; i<k; i++){
    int val;
    cin >> val;
    sum += val;
  }
  cout << sum - k + 1 << endl;
}

int main(){
  int n;
  cin >> n;
  while(n--) solve();
}
