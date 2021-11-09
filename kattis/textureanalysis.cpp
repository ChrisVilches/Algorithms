#include <bits/stdc++.h>

using namespace std;

bool even(string line) {
  int last_black = 0;
  int interval = -1;
  for (int i = 1; i < (int)line.size(); i++) {
    if (line[i] != '*') continue;

    if (interval == -1) {
      interval = i - last_black;
    } else if (interval != i - last_black) {
      return false;
    }

    last_black = i;
  }
  return true;
}

int main() {
  string line;
  int i = 1;
  while (getline(cin, line) && line != "END") {
    cout << (i++) << ' ' << (even(line) ? "EVEN" : "NOT EVEN") << endl;
  }
}
