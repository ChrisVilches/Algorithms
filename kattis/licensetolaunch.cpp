#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, x;
  scanf("%d", &n);
  int min_val = INT_MAX;
  int min_pos = -1;
  for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    if (x < min_val) {
      min_pos = i;
      min_val = x;
    }
  }
  printf("%d\n", min_pos);
}
