#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

int N;

// TODO: NEEDS REFACTOR!!!!!!!!!!!!!!!!!!!!!!!!!!!1

void solve() {
  set<pii> stacks;
  int total_coins = 0;

  for (int i = 0; i < N; i++) {
    pii s;
    s.second = i;
    cin >> s.first;
    stacks.emplace(s);

    total_coins += s.first;
  }

  vector<pii> moves;

  while (true) {
    set<pii>::iterator stack1 = prev(stacks.end());

    while (stack1->first == 0 && stack1 != stacks.begin()) --stack1;

    set<pii>::iterator stack2 = stack1;
    --stack2;
    while (stack2->first == 0 && stack2 != stacks.begin()) --stack2;

    if (stack1 == stacks.begin() && stack1->first == 0) break;
    if (stack2 == stacks.begin() && stack2->first == 0) break;

    total_coins -= 2;

    pii new_stack1 = make_pair(stack1->first - 1, stack1->second);
    pii new_stack2 = make_pair(stack2->first - 1, stack2->second);

    moves.push_back(make_pair(stack1->second, stack2->second));

    stacks.erase(stack1);
    stacks.erase(stack2);

    stacks.emplace(new_stack1);
    stacks.emplace(new_stack2);
  }

  if (total_coins == 0) {
    cout << "yes" << endl;

    for (pii move : moves) {
      cout << move.first + 1 << ' ' << move.second + 1 << endl;
    }
  } else {
    cout << "no" << endl;
  }
}

int main() {
  while (scanf("%d", &N) == 1) solve();
}
