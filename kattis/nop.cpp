#include <bits/stdc++.h>

using namespace std;

string line;

inline bool uppercase(char c) { return c >= 'A' && c <= 'Z'; }

void solve() {
  vector<int> instructions;

  int bytes = 1;
  for (int i = 1; i < (int)line.size(); i++) {
    if (uppercase(line[i])) {
      instructions.push_back(bytes);
      bytes = 1;
    } else
      bytes++;
  }

  instructions.push_back(bytes);

  int nops = 0;

  for (int i = 0; i < (int)instructions.size() - 1; i++) {
    int b = instructions[i];
    if (b % 4 == 0) continue;
    nops += 4 - b % 4;
  }

  cout << nops << endl;
}

int main() {
  while (getline(cin, line)) solve();
}
