#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<string> grid(n);

  for (auto& row : grid) cin >> row;

  map<int, int> empty;

  for (const auto& row : grid) {
    for (int j = 0; j < m; j++) empty[j] += row[j] == '.';
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << "S."[i < empty[j]];
    }

    cout << endl;
  }
}
