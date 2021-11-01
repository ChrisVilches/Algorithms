#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

int N;

inline void remove_coin_from_stack(set<pii>::iterator stack,
                                   set<pii, greater<pii>>& stacks) {
  stacks.erase(stack);
  pii updated_stack = *stack;
  updated_stack.first--;
  if (updated_stack.first > 0) stacks.emplace(updated_stack);
}

optional<vector<pii>> solve() {
  set<pii, greater<pii>> stacks;
  for (int i = 0; i < N; i++) {
    pii s;
    s.second = i;
    cin >> s.first;
    if (s.first > 0) stacks.emplace(s);
  }

  vector<pii> moves;

  while (!stacks.empty()) {
    if (stacks.size() == 1) return nullopt;

    set<pii>::iterator stack1 = stacks.begin();
    set<pii>::iterator stack2 = next(stack1);

    moves.push_back(make_pair(stack1->second, stack2->second));

    remove_coin_from_stack(stack1, stacks);
    remove_coin_from_stack(stack2, stacks);
  }

  return moves;
}

int main() {
  while (scanf("%d", &N) == 1) {
    optional<vector<pii>> moves = solve();

    if (moves.has_value()) {
      cout << "yes" << endl;
      for (pii move : moves.value())
        cout << move.first + 1 << ' ' << move.second + 1 << endl;
    } else
      cout << "no" << endl;
  }
}
