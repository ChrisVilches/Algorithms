#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    double v0, theta, x1, h1, h2;
    cin >> v0 >> theta >> x1 >> h1 >> h2;
    theta *= M_PI / 180;

    const double t = x1 / (cos(theta) * v0);
    const double y = v0 * t * sin(theta) - 0.5 * 9.81 * t * t;

    if (h1 + 1 < y && y < h2 - 1) {
      cout << "Safe" << endl;
    } else {
      cout << "Not Safe" << endl;
    }
  }
}
