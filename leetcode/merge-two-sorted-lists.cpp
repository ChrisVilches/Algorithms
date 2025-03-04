#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
};

class Solution {
 public:
  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode base;
    base.next = nullptr;

    ListNode* curr = &base;

    while (list1 != nullptr || list2 != nullptr) {
      ListNode*& node = list2 == nullptr || (list1 != nullptr && list1->val <= list2->val)
                            ? list1
                            : list2;

      curr->next = node;
      node = node->next;
      curr = curr->next;
    }

    return base.next;
  }
};
