#include <bits/stdc++.h>

using namespace std;

int main() {
  int a, b;

  while (scanf("%d%*c%d ", &a, &b) == 2) {
    long long R = (a * 100) + b;

    for (long long i = 1;; i++) {
      if ((36000L * i) % R == 0) {
        cout << (36000L * i) / R << endl;
        break;
      }
    }
  }
}
