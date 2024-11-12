#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  set<int> nums;

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    nums.emplace(x);
  }

  for (int i = 0; i < n - 1; i++) {
    int x;
    cin >> x;
    nums.erase(x);
  }

  cout << *nums.begin() << endl;
}
