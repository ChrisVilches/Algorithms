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

  int peek() const { return s.top()->val; }

  bool has_next() const { return !s.empty(); }
};

class Solution {
 public:
  vector<int> getAllElements(const TreeNode* const root1, const TreeNode* const root2) {
    vector<int> ans;

    BSTIterator it1(root1);
    BSTIterator it2(root2);

    while (it1.has_next() && it2.has_next()) {
      if (it1.peek() < it2.peek()) {
        ans.emplace_back(it1.next());
      } else {
        ans.emplace_back(it2.next());
      }
    }

    while (it1.has_next()) ans.emplace_back(it1.next());
    while (it2.has_next()) ans.emplace_back(it2.next());

    return ans;
  }
};
