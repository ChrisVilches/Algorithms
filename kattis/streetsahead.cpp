#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, q;
  cin >> n >> q;

  map<string, int> mapping;

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    mapping[s] = i;
  }

  while (q--) {
    string a, b;
    cin >> a >> b;
    const int i = mapping[a];
    const int j = mapping[b];
    cout << abs(i - j) - 1 << endl;
  }
}
