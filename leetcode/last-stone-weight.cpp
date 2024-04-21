#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> pq{stones.begin(), stones.end()};

    while (pq.size() > 1) {
      const int a = pq.top();
      pq.pop();
      const int b = pq.top();
      pq.pop();
      pq.push(abs(a - b));
    }

    return pq.top();
  }
};
