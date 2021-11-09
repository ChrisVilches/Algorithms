#include <bits/stdc++.h>

using namespace std;

#define MAX_STRING_LENGTH (2 * 100003)

// This program uses Suffix Array. Can be done easier with Suffix Tree.
// (Finding the longest match is a lot easier with a suffix tree.)

string city;

int N, sa[MAX_STRING_LENGTH], ranks[MAX_STRING_LENGTH], lcp[MAX_STRING_LENGTH],
    gap, S;

bool cmp(int x, int y) {
  if (ranks[x] != ranks[y]) return ranks[x] < ranks[y];
  x += gap, y += gap;
  return (x < S && y < S) ? ranks[x] < ranks[y] : x > y;
}

void suffix_array_build(const string& s) {
  S = s.size();
  vector<int> tmp;
  for (int i = 0; i < S; i++) {
    tmp.push_back(0);
  }
  for (int i = 0; i < S; ++i) ranks[i] = s[i], sa[i] = i;
  for (gap = 1;; gap <<= 1) {
    sort(sa, sa + S, cmp);
    for (int i = 1; i < S; ++i) tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
    for (int i = 0; i < S; ++i) ranks[sa[i]] = tmp[i];
    if (tmp[S - 1] == S - 1) break;
  }
}

int longest_prefix_match(int sa_pos, const string& city, const string& name,
                         int name_offset) {
  int pos_in_string = sa[sa_pos];
  int total = 0;
  for (int i = 0;; i++) {
    int pos_city = i + pos_in_string;
    int pos_s = i + name_offset;
    if (pos_s == (int)name.size() || pos_in_string == (int)city.size()) break;

    char c1 = city[pos_city];
    char c2 = name[pos_s];
    if (c1 != c2) break;
    total++;
  }

  return total;
}

int find_suffix_array_position(const string& name, int offset) {
  int match_pos = 0, longest_match = 0;
  int mid, left = 0, right = city.size();

  while (left < right) {
    mid = (right + left) / 2;
    int match = longest_prefix_match(mid, city, name, offset);
    if (match > longest_match) {
      longest_match = match;
      match_pos = mid;
    }

    bool greater = name.compare(offset, name.size() - offset, city, sa[mid],
                                city.size() - sa[mid]) > 0;

    if (greater)
      left = mid + 1;
    else
      right = mid;
  }

  return match_pos;
}

int necessary_for_name(const string& name) {
  int name_curr_pos = 0;
  int ans = 0;

  while (name_curr_pos < (int)name.size()) {
    int sa_pos = find_suffix_array_position(name, name_curr_pos);
    int pos_in_city = sa[sa_pos];

    if (city[pos_in_city] != name[name_curr_pos]) return -1;

    while (city[pos_in_city] == name[name_curr_pos]) {
      name_curr_pos++;
      pos_in_city++;
      if (pos_in_city >= (int)city.size() && name_curr_pos >= (int)name.size())
        break;
    }

    ans++;
  }

  return ans;
}

int main() {
  cin >> city >> N;

  suffix_array_build(city);

  for (int i = 0; i < N; i++) {
    string name;
    cin >> name;
    cout << necessary_for_name(name) << endl;
  }
}
