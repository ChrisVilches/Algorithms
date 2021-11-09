#include <bits/stdc++.h>
using namespace std;

int N;

void solve() {
  stack<int> s;
  queue<int> q;
  priority_queue<int> pq;

  bool is_stack = true;
  bool is_queue = true;
  bool is_priority_queue = true;

  while (N--) {
    int op, val;
    scanf("%d %d", &op, &val);

    if (op == 1) {
      s.push(val);
      q.push(val);
      pq.push(val);
    } else {
      if (s.empty()) {
        is_stack = false;
        is_queue = false;
        is_priority_queue = false;
        continue;
      }
      is_stack = is_stack && (s.top() == val);
      is_queue = is_queue && (q.front() == val);
      is_priority_queue = is_priority_queue && (pq.top() == val);

      s.pop();
      q.pop();
      pq.pop();
    }
  }

  int correct = is_stack + is_queue + is_priority_queue;

  if (correct == 0) {
    cout << "impossible" << endl;
  } else if (correct > 1) {
    cout << "not sure" << endl;
  } else {
    if (is_stack) cout << "stack" << endl;
    if (is_queue) cout << "queue" << endl;
    if (is_priority_queue) cout << "priority queue" << endl;
  }
}

int main() {
  while (scanf("%d", &N) == 1) solve();
}
