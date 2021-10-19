#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n;
  vector<int> p1, p2;

  cin >> n;
  for (int i = 0; i <= n; i++) {
    int c;
    cin >> c;
    p1.push_back(c);
  }

  cin >> n;
  for (int i = 0; i <= n; i++) {
    int c;
    cin >> c;
    p2.push_back(c);
  }

  vector<int> result;
  result.assign(p1.size() + p2.size() - 1, 0);
  for (int i = 0; i < p1.size(); i++) {
    for (int j = 0; j < p2.size(); j++) {
      int exp = i + j;
      int mult = p1[i] * p2[j];
      result[exp] += mult;
    }
  }

  cout << result.size() - 1 << endl;
  for (int c : result) {
    cout << c << " ";
  }
  cout << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
