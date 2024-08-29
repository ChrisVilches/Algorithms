#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    string num;
    cin >> num;

    int i = 1;

    for (; i < (int)num.length(); i++) {
      if (num[i - 1] > num[i]) break;
    }

    char digit = 0;

    for (; i < (int)num.length(); i++) {
      if (digit == 0 && num[i - 1] < num[i]) digit = num[i - 1];
      num[i] = max(digit, min(num[i], num[i - 1]));
    }

    cout << num << endl;
  }
}
