#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  double a;

  while (cin >> a) {
    cout << fixed << setprecision(15) << pow(a, 1 / a) << endl;
  }
}
