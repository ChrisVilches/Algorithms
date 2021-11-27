#include <bits/stdc++.h>

using namespace std;

string remove_repetition(string s) {
  if (s.size() < 4) return s;
  if (s[0] == s[2] && s[1] == s[3]) {
    return s.substr(2);
  }
  return s;
}

int main() {
  string s;
  bool space = false;

  while (cin >> s) {
    if (space) cout << ' ';
    cout << remove_repetition(s);
    space = true;
  }

  cout << endl;
}
