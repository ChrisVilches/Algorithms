#include <bits/stdc++.h>

using namespace std;

int main(){
  int x, y;
  cin >> x >> y;

  if((x * 4 + y * 3) % 2 == 0){
    cout << "possible" << endl;
  } else {
    cout << "impossible" << endl;
  }
}
