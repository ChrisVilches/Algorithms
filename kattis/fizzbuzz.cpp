#include <bits/stdc++.h>
using namespace std;

int main() {
  int F, B, N;
  cin >> F >> B >> N;

  for (int i = 1; i <= N; i++) {
    if (i % F == 0 && i % B == 0)
      cout << "FizzBuzz";
    else if (i % F == 0)
      cout << "Fizz";
    else if (i % B == 0)
      cout << "Buzz";
    else
      cout << i;

    cout << endl;
  }
}
