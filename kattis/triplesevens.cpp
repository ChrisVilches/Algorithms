#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  int total = 0;

  for (int i = 0; i < n * 3; i++) {
    int x;
    cin >> x;
    total += x == 7;
  }

  cout << (total == 3 ? 777 : 0) << endl;
}
