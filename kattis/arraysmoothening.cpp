#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  while (cin >> n >> k) {
    vector<int> nums(n);
    for (int& x : nums) cin >> x;

    unordered_map<int, int> freq;
    for (const int x : nums) freq[x]++;

    priority_queue<int> pq;
    for (const auto& [_, c] : freq) pq.push(c);
    pq.push(0);

    while (k--) {
      const int c = pq.top();
      pq.pop();
      pq.push(c - 1);
    }

    cout << pq.top() << endl;
  }
}
