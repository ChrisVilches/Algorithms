#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  TreeNode *const left, *const right;
};
#endif

class Solution {
 public:
  TreeNode* searchBST(TreeNode* const root, const int val) {
    TreeNode* curr = root;

    while (curr != nullptr) {
      if (curr->val == val) return curr;

      if (curr->val < val) {
        curr = curr->right;
      } else {
        curr = curr->left;
      }
    }

    return nullptr;
  }
};
