#include <bits/stdc++.h>

using namespace std;

double sphere_volume(double r) { return 4.0 * 3.1415 * pow(r, 3) / 3.0; }

int main() {
  int R, L;
  cin >> R >> L;
  printf("%d\n", (int)floor(L / sphere_volume(R)));
}
