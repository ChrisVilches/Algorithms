#include <bits/stdc++.h>

using namespace std;

vector<int> generate_primes(int a, int b) {
  vector<int> primes;
  bool flag;
  if (a <= 2) {
    a = 2;
    if (b >= 2) {
      primes.push_back(a);
      a++;
    }
  }

  if (a % 2 == 0) a++;

  for (int i = a; i <= b; i = i + 2) {
    bool flag = true;

    for (int j = 2; j * j <= i; ++j)
      if (i % j == 0) {
        flag = false;
        break;
      }

    if (flag) primes.push_back(i);
  }
  return primes;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int a, b;
    cin >> a >> b;

    vector<int> primes = generate_primes(a, b);
    for (int p : primes) printf("%d\n", p);
    printf("\n");
  }
}
