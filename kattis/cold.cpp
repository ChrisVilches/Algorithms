#include <bits/stdc++.h>

using namespace std;

int main(){
  int n, result = 0;
  cin >> n;

  while(n--) {
    int v;
    cin >> v;
    result += v < 0;
  }
  cout << result << endl;
}
