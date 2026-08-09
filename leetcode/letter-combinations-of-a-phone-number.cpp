#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<string> letterCombinations(const string digits) {
    if (digits.empty()) return {};

    const unordered_map<char, string> mapping = {
        {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
        {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
    };

    vector<string> ans;

    string curr;

    const function<void(int)> recur = [&](const size_t idx) {
      if (idx == digits.size()) {
        ans.emplace_back(curr);
        return;
      }

      for (const char c : mapping.at(digits[idx])) {
        curr += c;
        recur(idx + 1);
        curr.pop_back();
      }
    };

    recur(0);

    return ans;
  }
};
