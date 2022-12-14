#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    array<int, 2> count{0, 0};
    for (const char c : s) count[c == '0']++;
    const int max_count = *max_element(count.begin(), count.end());
    cout << (max_count >= 2 ? "NO" : "YES") << endl;
  }
}
