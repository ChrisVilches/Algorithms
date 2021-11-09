#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/find-divisors-natural-number-set-1/
int divisors_sum(int n) {
  int sum = 0;
  for (int i = 1; i <= sqrt(n); i++) {
    if (n % i == 0) {
      if (n / i == i)
        sum += i;
      else
        sum += i + (n / i);
    }
  }
  return sum;
}

void solve(int n) {
  int sum = divisors_sum(n) - n;
  cout << n << ' ';
  if (sum == n) {
    cout << "perfect";
  } else if (abs(n - sum) <= 2) {
    cout << "almost perfect";
  } else {
    cout << "not perfect";
  }
  cout << endl;
}

int main() {
  int n;
  while (scanf("%d", &n) == 1) solve(n);
}
