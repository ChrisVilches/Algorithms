#include <bits/stdc++.h>

using namespace std;

void solve(){
  double r, portions, desired;
  cin >> r >> portions >> desired;

  double scaling_factor = desired / portions;
  double scaled_weight;

  vector<tuple<string, double, double>> items;

  for(int i=0; i<r; i++){
    string name;
    double w, p;
    cin >> name >> w >> p;
    items.push_back(make_tuple(name, w, p));
    if(p == 100.0)
      scaled_weight = w * scaling_factor;
  }

  for(auto item : items){
    cout << get<0>(item);
    printf(" %f\n", get<2>(item) * scaled_weight/100);
  }
}

int main(){
  int t;
  cin >> t;
  for(int i=0; i<t; i++){
    printf("Recipe # %d\n", i+1);
    solve();
    printf("----------------------------------------\n");
  }
}
