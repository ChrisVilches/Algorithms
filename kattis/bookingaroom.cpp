#include <bits/stdc++.h>
using namespace std;

int main() {
  int r, n;
  cin >> r >> n;
  if (r == n) {
    cout << "too late" << endl;
    return 0;
  }

  vector<bool> used(r, false);

  while (n--) {
    int x;
    cin >> x;
    used[x - 1] = true;
  }

  for (int i = 0; i < r; i++) {
    if (!used[i]) {
      cout << i + 1 << endl;
      break;
    }
  }
}
