#include <bits/stdc++.h>

using namespace std;

int W, L, R1, R2;

bool circle_fits(int r) {
  int diam = r * 2;
  return diam <= W && diam <= L;
}

int main() {
  while (scanf("%d %d", &W, &L) == 2 && W != 0 && L != 0) {
    cin >> R1 >> R2;

    int x1 = R1;
    int y1 = W - R1;

    int x2 = L - R2;
    int y2 = R2;

    double dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

    bool fits = circle_fits(R1) && circle_fits(R2) && dist >= R1 + R2;

    cout << (fits ? 'S' : 'N') << endl;
  }
}
