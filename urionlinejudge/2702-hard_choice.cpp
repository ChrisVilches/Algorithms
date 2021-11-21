#include <iostream>
using namespace std;

int main() {
  int A, B, C;
  int a, b, c;

  cin >> A >> B >> C;
  cin >> a >> b >> c;

  cout << max(a - A, 0) + max(b - B, 0) + max(c - C, 0) << endl;
}
