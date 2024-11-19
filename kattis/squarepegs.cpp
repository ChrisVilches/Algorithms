#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<double> plots(n), houses(m);
  for (double& x : plots) cin >> x;
  for (double& x : houses) cin >> x;
  while (k--) {
    double s;
    cin >> s;
    houses.emplace_back(s / sqrt(2));
  }

  sort(plots.begin(), plots.end());
  sort(houses.begin(), houses.end());

  int j = 0;

  for (int i = 0; i < n && j < (int)houses.size(); i++) {
    j += houses[j] < plots[i];
  }

  cout << j << endl;
}
