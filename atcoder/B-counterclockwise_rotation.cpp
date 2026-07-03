#include <bits/stdc++.h>
using namespace std;

int main() {
  double x, y, d;
  cin >> x >> y >> d;

  const double rad = d * M_PI / 180;

  const double x0 = x * cos(rad) - y * sin(rad);
  const double y0 = x * sin(rad) + y * cos(rad);

  cout << fixed << setprecision(9) << x0 << " " << y0 << endl;
}
