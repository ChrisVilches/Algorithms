#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;

  while (cin >> n) {
    array<int, 4> digits{0, 0, 0, 0};

    int idx = 0;
    while (n > 0) {
      digits[idx++] = n % 10;
      n /= 10;
    }

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 9; j++) {
        int digit = -1;

        switch (j) {
          case 0:
            digit = digits[3];
            break;
          case 2:
            digit = digits[2];
            break;
          case 6:
            digit = digits[1];
            break;
          case 8:
            digit = digits[0];
            break;
        }

        if (digit == -1) {
          cout << " ";
          continue;
        }

        cout << ".*"[(digit & (1 << (3 - i))) != 0];
      }

      cout << endl;
    }
  }
}
