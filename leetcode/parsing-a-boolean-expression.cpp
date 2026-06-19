#include <bits/stdc++.h>
using namespace std;

class Solution {
  unordered_map<int, int> pairs;

  bool op(const char symbol, const bool a, const bool b) const {
    return symbol == '&' ? a && b : a || b;
  }

  bool eval(const string s, const int start, const int end) const {
    const char c = s[start];

    if (c == 't') return true;
    if (c == 'f') return false;
    if (c == '!') return !eval(s, start + 2, end - 1);

    bool res = c == '&';

    for (int i = start + 2; i < end; i += 2) {
      const char k = s[i];

      if (k == '!' || k == '&' || k == '|') {
        res = op(c, res, eval(s, i, pairs.at(i + 1)));
        i = pairs.at(i + 1);
      } else {
        res = op(c, res, eval(s, i, i));
      }
    }

    return res;
  }

 public:
  bool parseBoolExpr(const string expression) {
    stack<int> s;
    for (size_t i = 0; i < expression.size(); i++) {
      if (expression[i] == '(') {
        s.emplace(i);
      } else if (expression[i] == ')') {
        const int start = s.top();
        s.pop();
        pairs[start] = i;
      }
    }

    return eval(expression, 0, expression.size() - 1);
  }
};
