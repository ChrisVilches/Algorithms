#include <bits/stdc++.h>
using namespace std;

bool angles[181];

void set_angle_exists(const int m, const int h) {
  int diff = (m - h);
  int angle;

  do {
    angle = diff * 6;
    if (angle <= 180) angles[angle] = true;
    diff -= 30;
  } while (diff >= 30);
}

int main() {
  int minute = 0;
  int hour = 0;

  for (int i = 0; i <= 720; i++) {
    set_angle_exists(minute, hour);

    hour += i % 12 == 0;
    minute++;
  }

  int query;

  while (cin >> query) {
    cout << (angles[query] ? "Y" : "N") << endl;
  }
}
