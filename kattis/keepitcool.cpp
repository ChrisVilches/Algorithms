#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

int slot_initial[101], allocation[101];
bool cold[101];

int main() {
  int new_soda, students, slots, capacity;
  cin >> new_soda >> students >> slots >> capacity;

  memset(cold, true, sizeof cold);
  memset(allocation, 0, sizeof allocation);

  vector<pii> slot_order;

  for (int i = 0; i < slots; i++) {
    cin >> slot_initial[i];
    slot_order.push_back(make_pair(slot_initial[i], i));
  }

  sort(slot_order.begin(), slot_order.end());

  for (pii sa : slot_order) {
    int slot_idx = sa.second;

    while (new_soda > 0 && sa.first + allocation[slot_idx] < capacity) {
      new_soda--;
      allocation[slot_idx]++;
      cold[slot_idx] = false;
    }
  }

  int students_covered = 0;

  for (int i = 0; i < slots; i++)
    if (cold[i]) students_covered += slot_initial[i];

  if (students_covered < students) {
    cout << "impossible" << endl;
    return 0;
  }

  for (int i = 0; i < slots; i++) {
    cout << allocation[i] << ' ';
  }
  cout << endl;
}
