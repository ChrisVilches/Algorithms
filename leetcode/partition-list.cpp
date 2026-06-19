#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
};

class Solution {
 public:
  ListNode* partition(ListNode* const head, const int x) {
    ListNode lo, hi;
    ListNode* lo_ptr = &lo;
    ListNode* hi_ptr = &hi;

    for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
      if (curr->val < x) {
        lo_ptr->next = curr;
        lo_ptr = lo_ptr->next;
      } else {
        hi_ptr->next = curr;
        hi_ptr = hi_ptr->next;
      }
    }

    lo_ptr->next = hi.next;
    hi_ptr->next = nullptr;

    return lo.next;
  }
};
