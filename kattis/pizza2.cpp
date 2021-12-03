#include <bits/stdc++.h>
using namespace std;

int main() {
  double R, C;
  cin >> R >> C;

  double full_area = M_PI * pow(R, 2);
  double cheese_area = M_PI * pow(R - C, 2);

  printf("%.6f\n", 100 * cheese_area / full_area);
}
