#include <bits/stdc++.h>

using namespace std;

#define MAX_STRING_LENGTH 200001

string text;
int sa[MAX_STRING_LENGTH], ranks[MAX_STRING_LENGTH], gap, S;

bool cmp(int x, int y) {
  if (ranks[x] != ranks[y]) return ranks[x] < ranks[y];
  x += gap, y += gap;
  return (x < S && y < S) ? ranks[x] < ranks[y] : x > y;
}

void suffix_array_build(const string& s) {
  S = s.size();
  vector<int> tmp(S, 0);
  for (int i = 0; i < S; ++i) ranks[i] = s[i], sa[i] = i;
  for (gap = 1; tmp[S - 1] < S - 1; gap <<= 1) {
    sort(sa, sa + S, cmp);
    for (int i = 1; i < S; ++i) tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
    for (int i = 0; i < S; ++i) ranks[sa[i]] = tmp[i];
  }
}

bool lt(int idx, string& query) {
  int pos_in_string = sa[idx];

  for (int i = 0; i < query.size(); i++) {
    if (pos_in_string + i >= text.size()) return true;

    char c = text[pos_in_string + i];
    if (query[i] != c) return c < query[i];
  }

  return false;
}

bool equals(int idx, string& query) {
  int pos_in_string = sa[idx];
  for (int i = 0; i < query.size(); i++) {
    char c = text[pos_in_string + i];
    if (query[i] != c) return false;
  }

  return true;
}

int binary_search(bool first, string& x) {
  int low = 0;
  int high = text.size() - 1;
  int result = -1;

  while (low <= high) {
    int mid = (low + high) / 2;

    if (equals(mid, x)) {
      result = mid;
      if (first) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    } else if (lt(mid, x)) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return result;
}

pair<int, int> suffix_match_range(string& query_string) {
  return {binary_search(true, query_string), binary_search(false, query_string)};
}

int main() {
  int N;

  while (scanf("%d ", &N) == 1) {
    vector<string> queries(N);

    for (int i = 0; i < N; i++) getline(cin, queries[i]);

    getline(cin, text);

    suffix_array_build(text);

    for (string& q : queries) {
      auto [from, to] = suffix_match_range(q);

      vector<int> ans;

      for (int i = from; i <= to && i != -1; i++) {
        ans.push_back(sa[i]);
      }

      sort(ans.begin(), ans.end());

      for (int i : ans) {
        cout << i << ' ';
      }

      cout << endl;
    }
  }
}
