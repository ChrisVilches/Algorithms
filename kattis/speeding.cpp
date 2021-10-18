#include <bits/stdc++.h>

using namespace std;

int main(){
  int n;
  cin >> n;
  double t1, d1;
  cin >> t1 >> d1;
  double max_speed;
  while(--n){
    double t2, d2;
    cin >> t2 >> d2;
    double s = (d2-d1)/(t2-t1);
    max_speed = max(max_speed, s);
    t1 = t2;
    d1 = d2;
  }
  cout << floor(max_speed) << endl;
}
