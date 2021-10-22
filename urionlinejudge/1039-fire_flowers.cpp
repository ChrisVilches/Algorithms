#include <bits/stdc++.h>

using namespace std;

int main() {
  double r1, x1, y1;
  double r2, x2, y2;

  while (scanf("%lf %lf %lf %lf %lf %lf", &r1, &x1, &y1, &r2, &x2, &y2) == 6) {
    double center_dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    double required_radius = center_dist + r2;
    cout << (required_radius <= r1 ? "RICO" : "MORTO") << endl;
  }
}
