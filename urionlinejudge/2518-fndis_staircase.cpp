#include <bits/stdc++.h>

using namespace std;

int N, H, C, L;

int main() {
  while (scanf("%d %d %d %d", &N, &H, &C, &L) == 4) {
    printf("%.4f\n", N * sqrt(C * C + H * H) * L / 10000);
  }
}
