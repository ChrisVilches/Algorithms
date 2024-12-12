#include <bits/stdc++.h>
using namespace std;

class Solution {
  unordered_map<int, int> match;
  string s;

  bool is_digit(const char c) { return c >= '0' && c <= '9'; }

  int eval(const int from, const int to) {
    int res = 0;
    string curr_num;
    int sgn = 1;

    const auto add = [&](const int x) {
      res += sgn * x;
      sgn = 1;
    };

    for (int i = from; i <= to; i++) {
      if (s[i] == '-') sgn = -1;

      if (s[i] == '(') {
        add(eval(i + 1, match[i] - 1));
        i = match[i];
      }

      if (is_digit(s[i])) {
        curr_num += s[i];

        if (i == to || !is_digit(s[i + 1])) {
          add(stoi(curr_num));
          curr_num.clear();
        }
      }
    }

    return res;
  }

 public:
  int calculate(const string s) {
    const int n = s.size();
    this->s = s;
    stack<int> st;
    for (int i = 0; i < n; i++) {
      if (s[i] == '(') {
        st.push(i);
      } else if (s[i] == ')') {
        match[st.top()] = i;
        st.pop();
      }
    }
    return eval(0, n - 1);
  }
};
