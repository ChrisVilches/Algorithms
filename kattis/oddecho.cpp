#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  string line;
  for (int i = 0; i < N; i++) {
    cin >> line;
    if (i % 2 == 0) cout << line << endl;
  }
}
