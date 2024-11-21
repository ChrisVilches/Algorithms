#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;

  const int n = s.size();

  s += "__";

  const map<char, char> response{{'R', 'S'}, {'B', 'K'}, {'L', 'H'}};

  for (int i = 0; i < n; i++) {
    const unordered_set<char> combo{s[i], s[i + 1], s[i + 2]};

    if (combo.size() == 3 && !combo.count('_')) {
      cout << 'C';
      i += 2;
      continue;
    }

    cout << response.at(s[i]);
  }

  cout << endl;
}
