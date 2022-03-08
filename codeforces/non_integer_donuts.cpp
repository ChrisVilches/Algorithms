#include <bits/stdc++.h>
using namespace std;

long double read() {
  string in;
  cin >> in;
  in[0] = ' ';
  stringstream ss(in);
  long double res;
  ss >> res;
  return res;
}

int main() {
  int N;

  while (cin >> N) {
    long double value = read();

    int ans = 0;

    for (int i = 0; i < N; i++) {
      value += read();

      string digits = to_string(value);
      int dot_idx = distance(digits.begin(), find(digits.begin(), digits.end(), '.'));

      ans += digits[dot_idx + 1] != '0' || digits[dot_idx + 2] != '0';
    }

    cout << ans << endl;
  }
}
