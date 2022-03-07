#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

map<ll, ll> value_to_freq;
set<pii, greater<pii>> freq_to_value;

void upsert_freq(const ll value, const ll new_freq) {
  freq_to_value.erase({value_to_freq[value], value});

  if (new_freq > 0) freq_to_value.emplace(new_freq, value);
  value_to_freq[value] = new_freq;
}

void increase_freq(const ll value, const ll inc) {
  upsert_freq(value, value_to_freq[value] + inc);
}

bool possible() {
  int partitions = 0;

  while (!freq_to_value.empty()) {
    auto [freq, value] = *freq_to_value.begin();

    if (freq_to_value.size() == 1 && freq == 2) {
      partitions += 2;
      break;
    }

    if (freq == 1) {
      partitions++;
      upsert_freq(value, 0);
    }

    while (freq > 1) {
      increase_freq(value, -freq + (freq % 2 == 1));
      increase_freq(++value, freq / 2);
      freq /= 2;
    }
  }

  return partitions == 2;
}

int main() {
  int N;

  while (cin >> N) {
    value_to_freq.clear();
    freq_to_value.clear();
    vector<ll> nums(N);

    for (int i = 0; i < N; i++) cin >> nums[i];

    for (int n : nums) value_to_freq[n]++;

    for (auto it = value_to_freq.begin(); it != value_to_freq.end(); it++)
      freq_to_value.emplace(it->second, it->first);

    cout << (possible() ? "Y" : "N") << endl;
  }
}
