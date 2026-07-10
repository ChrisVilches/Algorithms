#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    for (int i = 0; i < n; i++) {
      if (a[i] > b[i]) swap(a[i], b[i]);
    }

    const long long a_max = *max_element(a.begin(), a.end());
    const long long b_sum = accumulate(b.begin(), b.end(), 0LL);

    cout << a_max + b_sum << endl;
  }
}
