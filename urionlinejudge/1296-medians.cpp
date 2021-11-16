#include <bits/stdc++.h>

using namespace std;

double area(double a, double b, double c) {
  if (a + b <= c) return -1;

  return sqrt(2 * pow(a, 2) * pow(b, 2) + 2 * pow(b, 2) * pow(c, 2) +
              2 * pow(c, 2) * pow(a, 2) - pow(a, 4) - pow(b, 4) - pow(c, 4)) /
         3.0;
}

int main() {
  double a, b, c;

  while (scanf("%lf %lf %lf", &a, &b, &c) == 3) {
    double medians[] = {a, b, c};
    sort(medians, medians + 3);
    printf("%.3f\n", area(medians[0], medians[1], medians[2]));
  }
}
