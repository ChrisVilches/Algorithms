#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  const TreeNode *const left, *const right;
};
#endif

class BSTIterator {
  stack<const TreeNode*> s;

  void go_left(const TreeNode* node) {
    while (node != nullptr) {
      s.emplace(node);
      node = node->left;
    }
  }

 public:
  BSTIterator(const TreeNode* const root) { go_left(root); }

  int next() {
    const int result = s.top()->val;
    const TreeNode* const node = s.top();
    s.pop();

    if (node->right != nullptr) {
      go_left(node->right);
    }

    return result;
  }

  bool hasNext() { return !s.empty(); }
};
