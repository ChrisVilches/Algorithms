#include <bits/stdc++.h>

using namespace std;

void solve(){
  int n;
  cin >> n;
  unordered_set<string> s;
  while(n--){
    string city;
    cin >> city;
    s.emplace(city);
  }
  cout << s.size() << endl;
}

int main(){
  int T;
  cin >> T;
  while(T--) solve();
}
