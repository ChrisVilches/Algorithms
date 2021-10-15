#include <bits/stdc++.h>

using namespace std;

int r, c;

bool possible(set<int>& x_set, set<int>& y_set){
  set<int> x_set_copy = x_set;
  set<int> y_set_copy = y_set;

  while(x_set.size() > 0){
    auto remaining_x = x_set.begin();
    auto match_y = y_set_copy.lower_bound(*remaining_x);
    if(match_y == y_set_copy.end())
      return false;
    x_set.erase(remaining_x);
  }
  while(y_set.size() > 0){
    auto remaining_y = y_set.begin();
    auto match_x = x_set_copy.lower_bound(*remaining_y);
    if(match_x == x_set_copy.end())
      return false;
    y_set.erase(remaining_y);
  }

  return true;
}

int main(){
  while(scanf("%d %d", &r, &c) == 2){
    int val;
    set<int> x_set, y_set;

    for(int i=0; i<r; i++){
      cin >> val;
      x_set.emplace(val);
    }
    for(int i=0; i<c; i++){
      cin >> val;
      y_set.emplace(val);
    }
    cout << (possible(x_set, y_set) ? "possible" : "impossible") << endl;
  }
  return 0;
}
