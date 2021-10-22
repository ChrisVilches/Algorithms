#include <bits/stdc++.h>

using namespace std;

double dist(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
  double housex, housey;
  double schoolx, schooly;
  double speed;

  double lowerx, lowery;
  double upperx, uppery;

  while (scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf", &housex, &housey,
               &schoolx, &schooly, &speed, &lowerx, &lowery, &upperx,
               &uppery) == 9) {
    double path1 = dist(housex, housey, upperx, uppery) +
                   dist(upperx, uppery, schoolx, schooly);
    double path2 = dist(housex, housey, lowerx, lowery) +
                   dist(lowerx, lowery, schoolx, schooly);
    double min_path = min(path1, path2);

    printf("%.1lf\n", min_path / speed);
  }
}
