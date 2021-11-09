#include <bits/stdc++.h>

using namespace std;

void solve(){
  int n, s, max_size = 0;
  queue<int> segment;
  unordered_set<int> snowflakes;
  cin >> n;
  while(n--){
    cin >> s;
    if(snowflakes.find(s) != snowflakes.end()){
      while(!segment.empty()){
        int top = segment.front();
        segment.pop();
        snowflakes.erase(top);
        if(s == top) break;
      }
    }
    segment.push(s);
    snowflakes.emplace(s);
    max_size = max(max_size, (int)snowflakes.size());
  }
  cout << max_size << endl;
}

int main(){
  int T;
  cin >> T;
  while(T--) solve();
}
