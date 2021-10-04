#include <bits/stdc++.h>

using namespace std;
double PI = 3.141592653589793238462643383279;

int main(){
  double a, b;
  cin >> a >> b;

  double R = b/(2 * PI);

  if(a <= PI * R * R){
    cout << "Diablo is happy!" << endl;
  } else {
    cout << "Need more materials!" << endl;
  }
}
