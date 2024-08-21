#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, w;
  cin >> w >> n;
  int area = 0;
  while (n--) {
    int x, y;
    cin >> x >> y;
    area += x * y;
  }
  cout << area / w << endl;
}
