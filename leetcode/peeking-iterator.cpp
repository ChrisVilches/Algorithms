#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
class Iterator {
 public:
  Iterator(const vector<int>& nums);
  int next();
  bool hasNext() const;
};
#endif

class PeekingIterator : public Iterator {
  int stored_val = 0;

 public:
  PeekingIterator(const vector<int>& nums) : Iterator(nums) {}

  int peek() {
    if (stored_val != 0) return stored_val;
    return stored_val = next();
  }

  int next() {
    if (stored_val != 0) {
      const int ret = stored_val;
      stored_val = 0;
      return ret;
    }

    return Iterator::next();
  }

  bool hasNext() const { return stored_val != 0 || Iterator::hasNext(); }
};
