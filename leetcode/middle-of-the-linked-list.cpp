#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct ListNode {
  const int val;
  ListNode* const next;
};
#endif

class Solution {
 public:
  ListNode* middleNode(ListNode* const head) {
    ListNode* a = head;
    ListNode* b = head;

    while (true) {
      b = b->next;

      if (b == nullptr) return a;
      a = a->next;

      if (b->next != nullptr) b = b->next;
    }

    return a;
  }
};
