#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxNumberOfBalloons(const string text) {
    unordered_map<char, int> freq;
    for (const char c : text) freq[c]++;

    freq['l'] /= 2;
    freq['o'] /= 2;

    return min({freq['b'], freq['a'], freq['l'], freq['o'], freq['n']});
  }
};
