#include <bits/stdc++.h>
using namespace std;

class MyCalendar {
  using pii = pair<int, int>;
  set<pii> events;

  bool intersect(const pii a, const pii b) const {
    return !(a.second <= b.first || b.second <= a.first);
  }

  bool can_add(const pii ev) const {
    if (events.empty()) return true;

    const auto it = events.lower_bound({ev.first, INT_MIN});

    if (it != events.end() && intersect(ev, *it)) return false;
    if (it != events.begin() && intersect(ev, *prev(it))) return false;

    return true;
  }

 public:
  bool book(const int start, const int end) {
    return can_add({start, end}) && events.emplace(start, end).second;
  }
};
