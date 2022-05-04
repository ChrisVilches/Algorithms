#include <bits/stdc++.h>
using namespace std;

string day;
int N;

unordered_map<string, int> weekday_map{{"Mon", 0}, {"Tue", 1}, {"Wed", 2}, {"Thu", 3},
                                       {"Fri", 4}, {"Sat", 5}, {"Sun", 6}};

bool is_weekday(const int day) { return (day % 7) < 5; }

int day_minus(const int day, const int d) { return day - (d % 7); }

bool is_cyclic_day(int day) {
  day %= 7;
  return day == 0 || day == 2 || day == 4;
}

int find_current_period_day(const int deposit_initial_day, const int deposit) {
  if (is_cyclic_day(deposit_initial_day) && deposit >= 91)
    return find_current_period_day(deposit_initial_day, deposit % 91);

  int period_day = 0;

  for (int i = 0; i < deposit; i++) {
    if (period_day % 30 == 0) {
      if (deposit >= 91 && is_cyclic_day(deposit_initial_day + i)) {
        return find_current_period_day(deposit_initial_day + i, deposit - i);
      }

      if (is_weekday(deposit_initial_day + i)) period_day++;

    } else {
      period_day++;
    }
  }

  return period_day;
}

void solve() {
  vector<int> deposits(N);

  for (int i = 0; i < N; i++) {
    cin >> deposits[i];
  }

  const int initial_day = weekday_map[day];

  int ans = INT_MAX;

  for (int deposit : deposits) {
    const int deposit_initial_day = day_minus(initial_day, deposit);
    int period_day = find_current_period_day(deposit_initial_day, deposit);

    for (int i = 0;; i++) {
      const bool at_least_one_day_elapsed = period_day > 0 || deposit > 0;

      if (at_least_one_day_elapsed && period_day % 30 == 0) {
        if (is_weekday(initial_day + i)) {
          ans = min(ans, i);
          break;
        }
      } else {
        period_day++;
      }
    }
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> day >> N) solve();
}
