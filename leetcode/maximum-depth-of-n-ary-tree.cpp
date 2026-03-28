#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
class Node {
 public:
  const int val;
  const vector<Node*> children;
};
#endif

class Solution {
 public:
  int maxDepth(const Node* const root) {
    if (root == nullptr) return 0;
    int res = 0;

    for (const Node* const n : root->children) {
      res = max(res, maxDepth(n));
    }

    return 1 + res;
  }
};
