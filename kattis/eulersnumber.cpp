#include <bits/stdc++.h>
using namespace std;

double one_div_factorial(const int n) {
  if (n > 20) return 0;

  double fact = 1;

  for (int i = 1; i <= n; i++) {
    fact *= i;
  }

  return 1 / fact;
}

int main() {
  int n;
  cin >> n;

  double ans = 0;

  for (int i = 0; i <= n; i++) {
    ans += one_div_factorial(i);
  }

  cout << fixed << setprecision(15) << ans << endl;
}
