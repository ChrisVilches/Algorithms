#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct ListNode {
  const int val;
  ListNode* const next;
};

struct TreeNode {
  const int val;
  const TreeNode *const left, *const right;
  TreeNode(const int x, const TreeNode* const l, const TreeNode* const r)
      : val(x), left(l), right(r) {}
};
#endif

class Solution {
  ListNode* middle(ListNode* const start, ListNode* const end) {
    ListNode* a = start;
    ListNode* b = start;

    while (true) {
      b = b->next;

      if (b == end) return a;
      a = a->next;

      if (b->next != end) b = b->next;
    }

    return a;
  }

  TreeNode* divide(ListNode* const start, ListNode* const end) {
    if (start == end) return nullptr;

    ListNode* const m = middle(start, end);

    return new TreeNode(m->val, divide(start, m), divide(m->next, end));
  }

 public:
  TreeNode* sortedListToBST(ListNode* const head) { return divide(head, nullptr); }
};
