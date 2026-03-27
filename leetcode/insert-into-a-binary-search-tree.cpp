#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  TreeNode *left, *right;
  TreeNode(const int x) : val(x), left(nullptr), right(nullptr) {}
};
#endif

class Solution {
 public:
  TreeNode* insertIntoBST(TreeNode* const root, const int val) {
    if (root == nullptr) return new TreeNode(val);

    TreeNode* curr = root;

    while (true) {
      if (curr->val < val && curr->right == nullptr) {
        curr->right = new TreeNode(val);
        break;
      }

      if (val < curr->val && curr->left == nullptr) {
        curr->left = new TreeNode(val);
        break;
      }

      curr = curr->val < val ? curr->right : curr->left;
    }

    return root;
  }
};
