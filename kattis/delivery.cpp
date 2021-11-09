#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

int N, K;

int travel_dist(vector<pii>& locations) {
  int dist = 0;
  for (int i = 0; i < (int)locations.size(); i++) {
    auto [address, letters] = locations[i];

    if (letters <= 0) continue;

    while (letters > 0) {
      dist += abs(address);
      letters -= K;

      if (letters < 0) {
        int remainder = -letters;
        int j = i + 1;
        while (j < (int)locations.size() && remainder > 0) {
          locations[j].second--;
          remainder--;
          if (locations[j].second == 0) j++;
        }
      } else if (letters > 0) {
        dist += abs(address);
      }
    }

    dist += abs(address);
  }
  return dist;
}

int main() {
  cin >> N >> K;

  vector<pii> left_locations, right_locations;

  for (int i = 0; i < N; i++) {
    int address, letters;
    cin >> address >> letters;
    if (address < 0)
      left_locations.push_back(make_pair(address, letters));
    else
      right_locations.push_back(make_pair(address, letters));
  }

  sort(left_locations.begin(), left_locations.end());
  sort(right_locations.rbegin(), right_locations.rend());

  for (pii& loc : right_locations) loc.first *= -1;

  cout << travel_dist(left_locations) + travel_dist(right_locations) << endl;
}
