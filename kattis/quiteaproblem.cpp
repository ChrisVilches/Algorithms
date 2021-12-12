#include <bits/stdc++.h>
using namespace std;

int main() {
  string line;

  while (getline(cin, line)) {
    transform(line.begin(), line.end(), line.begin(),
              [](char c) { return tolower(c); });

    if (line.find("problem") != line.npos)
      cout << "yes" << endl;
    else
      cout << "no" << endl;
  }
}
