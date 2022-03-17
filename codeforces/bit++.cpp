#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  int x = 0;

  while (N--) {
    string op;
    cin >> op;

    if (op.find('+') != op.npos) {
      x++;
    } else {
      x--;
    }
  }

  cout << x << endl;
}
