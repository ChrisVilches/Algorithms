#include <bits/stdc++.h>
using namespace std;

int N;

bool solve() {
  vector<string> lines(N);

  set<char> first_letters;

  for (int i = 0; i < N; i++) {
    cin >> lines[i];

    first_letters.insert(lines[i][0]);
  }

  for (const string& line : lines) {
    bool found = true;

    for (const char c : line) {
      if (!first_letters.count(c)) {
        found = false;
        break;
      }
    }

    if (found) return true;
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N) {
    cout << (solve() ? "Y" : "N") << endl;
  }
}
