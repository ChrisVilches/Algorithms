#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* result = new ListNode();
    ListNode* curr = result;
    int extra = 0;

    while (true) {
      int sum = extra;
      if (l1) sum += l1->val;
      if (l2) sum += l2->val;

      if (sum > 9) {
        extra = 1;
        sum -= 10;
      } else {
        extra = 0;
      }

      curr->val = sum;

      if (l1) l1 = l1->next;
      if (l2) l2 = l2->next;

      if (!l1 && !l2) {
        if (extra > 0) {
          curr->next = new ListNode(1);
        }
        break;
      }

      curr->next = new ListNode();
      curr = curr->next;
    }

    return result;
  }
};
