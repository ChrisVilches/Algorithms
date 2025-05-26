#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int longestValidParentheses(string s) {
    stack<int> st;
    vector<bool> valid(s.size(), false);

    for (size_t i = 0; i < s.size(); i++) {
      const char c = s[i];

      if (c == '(') {
        st.push(i);
      } else if (!st.empty()) {
        const int j = st.top();
        st.pop();
        valid[i] = true;
        valid[j] = true;
      }
    }

    int ans = 0;
    int curr = 0;

    for (const bool v : valid) {
      curr = v ? curr + 1 : 0;
      ans = max(ans, curr);
    }

    return ans;
  }
};
