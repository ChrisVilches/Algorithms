#include <bits/stdc++.h>

using namespace std;

int main() {
  string s;
  cin >> s;

  int total = 0;

  int t = 0;
  int g = 0;
  int c = 0;

  for (int i = 0; i < (int)s.size(); i++) {
    char ch = s[i];

    if (ch == 'T')
      t++;
    else if (ch == 'G')
      g++;
    else if (ch == 'C')
      c++;
  }

  total += pow(t, 2);
  total += pow(g, 2);
  total += pow(c, 2);

  while (t > 0 && g > 0 && c > 0) {
    t--;
    g--;
    c--;
    total += 7;
  }

  cout << total << endl;
}
