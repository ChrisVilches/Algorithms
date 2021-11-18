#include <bits/stdc++.h>

using namespace std;

int factorial(int n) {
  if (n <= 1) return 1;
  return n * factorial(n - 1);
}

int main() {
  int T, N;
  cin >> T;
  while (T--) {
    cin >> N;
    cout << factorial(N) % 10 << endl;
  }
}
