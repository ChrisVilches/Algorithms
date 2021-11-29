#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  while (N--) {
    int i, j;
    cin >> i >> j;

    if (i == j)
      cout << i * 2 - (i % 2 == 1) << endl;
    else if (i == j + 2)
      cout << i + j - (i % 2 == 1) << endl;
    else
      cout << "No Number" << endl;
  }
}
