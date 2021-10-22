#include <bits/stdc++.h>

using namespace std;

int main() {
  int a, b, c, d;
  int pos = 0;
  int max_val = INT_MIN;
  for (int i = 0; i < 5; i++) {
    cin >> a >> b >> c >> d;
    if (max_val < a + b + c + d) {
      pos = i + 1;
      max_val = a + b + c + d;
    }
  }
  printf("%d %d\n", pos, max_val);
}
