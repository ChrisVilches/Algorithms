#include <bits/stdc++.h>

using namespace std;
typedef long double ld;

ld dist(ld x1, ld y1, ld x2, ld y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
  ld housex, housey;
  ld schoolx, schooly;
  ld speed;

  ld lowerx, lowery;
  ld upperx, uppery;

  while (scanf("%Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf", &housex, &housey,
               &schoolx, &schooly, &speed, &lowerx, &lowery, &upperx,
               &uppery) == 9) {
    ld horizontal_dist = dist(lowerx, 0, upperx, 0);
    ld p1 = dist(housex, housey, lowerx, uppery) +
            dist(upperx, uppery, schoolx, schooly);
    ld p2 = dist(housex, housey, lowerx, lowery) +
            dist(upperx, lowery, schoolx, schooly);
    ld min_path = min(p1, p2);

    printf("%.1Lf\n", (min_path + horizontal_dist) / speed);
  }
}
