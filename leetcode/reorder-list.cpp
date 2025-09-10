#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  ListNode* next;
};

class Solution {
 public:
  void reorderList(ListNode* head) {
    int length = 0;
    stack<ListNode*> nodes;

    for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
      nodes.emplace(curr);
      length++;
    }

    ListNode* curr = head;
    const int times = (length / 2) - (length % 2 == 0);

    for (int it = 0; it < times; it++) {
      ListNode* next = curr->next;

      ListNode* last = nodes.top();
      nodes.pop();
      nodes.top()->next = nullptr;

      curr->next = last;
      last->next = next;

      curr = next;
    }
  }
};
