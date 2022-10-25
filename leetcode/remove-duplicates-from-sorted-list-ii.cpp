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
  unordered_map<int, int> get_counts(ListNode* head) {
    unordered_map<int, int> res;

    for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
      res[curr->val]++;
    }

    return res;
  }

  ListNode* deleteDuplicates(ListNode* head) {
    const unordered_map<int, int> counts = get_counts(head);

    ListNode* first_node = nullptr;
    ListNode* last_node = nullptr;

    for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
      if (counts.at(curr->val) != 1) continue;

      if (last_node == nullptr) {
        first_node = curr;
        last_node = curr;
      } else {
        last_node->next = curr;
        last_node = curr;
      }
    }

    if (last_node) last_node->next = nullptr;

    return first_node;
  }
};
