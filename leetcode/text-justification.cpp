#include <bits/stdc++.h>
using namespace std;

class Solution {
  int full_size(const vector<string>& line) {
    int total = line.size() - 1;
    for (const auto& s : line) total += s.size();
    return total;
  }

 public:
  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<vector<string>> lines{vector<string>()};

    for (const auto& s : words) {
      vector<string> next_line = lines.back();
      next_line.emplace_back(s);

      if (full_size(next_line) > maxWidth) {
        lines.emplace_back(vector<string>());
      }

      lines.back().emplace_back(s);
    }

    vector<string> result;

    for (int i = 0; i < (int)lines.size(); i++) {
      const bool add_right = i == (int)lines.size() - 1 || (int)lines[i].size() == 1;

      const int remaining = maxWidth - full_size(lines[i]);

      if (!add_right) {
        const int spaces = lines[i].size() - 1;

        const string add(remaining / spaces, ' ');

        for (int k = 0; k < spaces; k++) lines[i][k] += add;
        for (int k = 0; k < remaining % spaces; k++) lines[i][k] += ' ';
      }

      string line = lines[i].front();

      for (int j = 1; j < lines[i].size(); j++) {
        line += ' ' + lines[i][j];
      }

      if (add_right) {
        line += string(remaining, ' ');
      }

      result.emplace_back(line);
    }

    return result;
  }
};
