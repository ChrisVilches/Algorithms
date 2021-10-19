#include <bits/stdc++.h>

using namespace std;

int main() {
  string line;
  cin >> line;
  int count = 0;
  for (int i = 0; i < (int)line.size(); i++) {
    if (line[i] == 'e') count++;
  }

  count *= 2;

  cout << 'h';
  while (count--) {
    cout << 'e';
  }
  cout << 'y' << endl;
}
