#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  TreeNode* sortedArrayToBST(const vector<int>& nums) {
    if (nums.empty()) return nullptr;

    const int m = nums.size() / 2;
    const vector<int> left{nums.begin(), nums.begin() + m};
    const vector<int> right{nums.begin() + m + 1, nums.end()};
    return new TreeNode(nums[m], sortedArrayToBST(left), sortedArrayToBST(right));
  }
};
