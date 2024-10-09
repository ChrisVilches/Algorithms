#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;
  int count = 0;
  bool after = false;

  for (const char c : s) {
    const int value = c == '|';
    count += after ? -value : value;
    if (c == '(') after = true;
  }

  if (count == 0) {
    cout << "correct" << endl;
  } else {
    cout << "fix" << endl;
  }
}
