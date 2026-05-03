#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  const TreeNode *const left, *const right;
};
#endif

class Solution {
  stack<const TreeNode*> s;

  void go_left(const TreeNode* node) {
    while (node != nullptr) {
      s.emplace(node);
      node = node->left;
    }
  }

 public:
  int kthSmallest(const TreeNode* const root, const int k) {
    go_left(root);

    for (int i = 0; i < k - 1; i++) {
      const TreeNode* const node = s.top();
      s.pop();

      if (node->right != nullptr) {
        go_left(node->right);
      }
    }

    return s.top()->val;
  }
};
