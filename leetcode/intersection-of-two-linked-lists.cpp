#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
};

class Solution {
 public:
  ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    ListNode* res = nullptr;

    for (auto n = headA; n; n = n->next) n->val *= -1;

    for (auto n = headB; n && !res; n = n->next) {
      if (n->val < 0) res = n;
    }

    for (auto n = headA; n; n = n->next) n->val = abs(n->val);

    return res;
  }
};
