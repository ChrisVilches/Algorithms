#include <bits/stdc++.h>

using namespace std;

int N, K;

set<pair<int, int>> occurrences_set(const vector<int>& nums) {
  map<int, int> occurrences;
  for (int i = 1; i <= K; i++) occurrences[i] = 0;
  for (int i : nums) occurrences[i]++;

  set<pair<int, int>> res;

  for (auto it = occurrences.begin(); it != occurrences.end(); it++)
    res.emplace(make_pair(it->second, it->first));

  return res;
}

bool is_complete(const vector<int>& nums) {
  set<pair<int, int>> occurrences = occurrences_set(nums);
  int count = occurrences.begin()->first;
  for (auto it = occurrences.begin(); it != occurrences.end(); it++)
    if (it->first != count) return false;
  return true;
}

void try_add(vector<int> nums) {
  pair<int, int> lowest = *occurrences_set(nums).begin();
  nums.push_back(lowest.second);
  if (is_complete(nums)) {
    printf("+%d\n", lowest.second);
    exit(0);
  }
}

void try_remove(vector<int> nums) {
  pair<int, int> highest = *occurrences_set(nums).rbegin();
  nums.erase(find(nums.begin(), nums.end(), highest.second));
  if (is_complete(nums)) {
    printf("-%d\n", highest.second);
    exit(0);
  }
}

void try_add_and_remove(vector<int> nums) {
  set<pair<int, int>> s = occurrences_set(nums);
  pair<int, int> lowest = *s.begin();
  pair<int, int> highest = *s.rbegin();
  nums.push_back(lowest.second);
  nums.erase(find(nums.begin(), nums.end(), highest.second));
  if (is_complete(nums)) {
    printf("-%d +%d\n", highest.second, lowest.second);
    exit(0);
  }
}

int main() {
  cin >> K >> N;

  vector<int> nums;

  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    nums.push_back(x);
  }

  try_add(nums);
  try_remove(nums);
  try_add_and_remove(nums);
  cout << '*' << endl;
}
