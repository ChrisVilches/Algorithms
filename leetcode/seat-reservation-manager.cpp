#include <bits/stdc++.h>
using namespace std;

class SeatManager {
  priority_queue<int, vector<int>, greater<int>> seats;

 public:
  SeatManager(const int n) {
    for (int i = 1; i <= n; i++) seats.emplace(i);
  }

  int reserve() {
    const int val = seats.top();
    seats.pop();
    return val;
  }

  void unreserve(const int seatNumber) { seats.emplace(seatNumber); }
};
