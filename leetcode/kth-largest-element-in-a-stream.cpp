#include <bits/stdc++.h>
using namespace std;

class KthLargest {
  size_t k;
  priority_queue<int, vector<int>, greater<int>> pq;

 public:
  KthLargest(const int k_input, const vector<int>& nums) {
    this->k = k_input;
    for (const int x : nums) add(x);
  }

  int add(const int val) {
    pq.emplace(val);
    if (pq.size() > k) pq.pop();
    return pq.top();
  }
};
