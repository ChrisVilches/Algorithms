#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  ListNode* next;
};

class Solution {
 public:
  ListNode* swapPairs(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;

    ListNode* ret = head->next;
    ListNode* curr = head;

    while (curr != nullptr && curr->next != nullptr) {
      ListNode* first = curr;
      ListNode* second = first->next;
      ListNode* third = second->next;

      first->next = third;
      second->next = first;

      if (third != nullptr && third->next != nullptr) {
        first->next = third->next;
      }

      curr = third;
    }

    return ret;
  }
};
