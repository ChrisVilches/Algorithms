#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tiii;

string line;
enum { CONSUMPTION, GOAL, LEAK, MECHANIC, STATION };

tiii parse_event(string& event) {
  stringstream ss(event);
  string skip;

  int distance, event_type, n = 0;
  ss >> distance;

  if (event.find("Fuel consumption") != event.npos) {
    event_type = CONSUMPTION;
    ss >> skip >> skip >> n;
  } else if (event.find("Goal") != event.npos)
    event_type = GOAL;
  else if (event.find("Mechanic") != event.npos)
    event_type = MECHANIC;
  else if (event.find("Gas station") != event.npos)
    event_type = STATION;
  else if (event.find("Leak") != event.npos)
    event_type = LEAK;

  return {distance, event_type, n};
}

bool possible(const double tank, vector<tiii>& events) {
  double curr_gas = tank;
  int gas_per_100km = 0;
  int leaks = 0;
  int prev_dist = 0;

  for (auto [distance, event_type, n] : events) {
    curr_gas -= (distance - prev_dist) * gas_per_100km / 100.0;
    curr_gas -= (distance - prev_dist) * leaks;

    prev_dist = distance;

    if (curr_gas < 0) return false;

    switch (event_type) {
      case CONSUMPTION:
        gas_per_100km = n;
        break;
      case LEAK:
        leaks++;
        break;
      case MECHANIC:
        leaks = 0;
        break;
      case STATION:
        curr_gas = tank;
        break;
    }
  }

  return true;
}

double calculate(vector<tiii>& events) {
  double left = 0;
  double right = 1e9;

  while (right - left > 0.000001) {
    double mid = (right + left) / 2;

    if (possible(mid, events))
      right = mid;
    else
      left = mid;
  }

  return left;
}

int main() {
  vector<tiii> events;

  while (getline(cin, line)) {
    events.push_back(parse_event(line));

    if (get<1>(events.back()) == GOAL) {
      printf("%.3f\n", calculate(events));
      events.clear();
    }
  }
}
