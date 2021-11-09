#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int X[52], Y[52], S, H;

bool safe(int x, int y){
  float dist = 0;

  for(int i=0; i<H; i++){
    if(x == X[i] && y == Y[i]) return false;
    float d = sqrt(pow(x - X[i], 2) + pow(y - Y[i], 2));
    dist = max(dist, d);
  }

  return (x + dist <= S) && (y + dist <= S) && (x - dist >= 0) && (y - dist >= 0);
}

optional<pii> solve(){
  cin >> S >> H;
  for(int i=0; i<H; i++)
    cin >> X[i] >> Y[i];

  for(int i=0; i<=S; i++)
    for(int j=0; j<=S; j++)
      if(safe(i, j))
        return make_pair(i, j);

  return nullopt;
}

int main(){
  int cases;
  cin >> cases;
  while(cases--){
    optional<pii> point = solve();

    if(point.has_value())
      cout << point.value().first << " " << point.value().second << endl;
    else
      cout << "poodle" << endl;
  }
}
