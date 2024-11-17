#include <bits/stdc++.h>
using namespace std;

int main() {
  string line;

  while (getline(cin, line)) {
    string clean;
    for (const char c : line) {
      if (c == ' ') continue;
      clean += c;
    }

    for (char& c : clean) {
      if (c == ',') c = ' ';
    }

    stringstream ss(clean);

    double ans = 0;
    double x;

    while (ss >> x) ans += x;

    cout << fixed << setprecision(9) << ans << endl;
  }
}
