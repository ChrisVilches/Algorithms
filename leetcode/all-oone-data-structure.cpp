#include <bits/stdc++.h>
using namespace std;

class Ordering {
  struct Node {
    int val, prev = -1, next = -1;
  };

  unordered_map<int, Node> store;

  void remove(const int i) {
    const int p = store[i].prev;
    const int n = store[i].next;
    if (p != -1) store[p].next = n;
    if (n != -1) store[n].prev = p;
    store.erase(i);
  }

 public:
  Ordering() {
    store[0] = {100'000, -1, INT_MAX};
    store[INT_MAX] = {100'000, 0, -1};
  }

  int max_key() const { return store.at(INT_MAX).prev; }

  int min_key() const {
    if (store.size() == 2) return 0;
    return store.at(0).next;
  }

  void inc(const int i) {
    if (store.count(i + 1)) {
      store[i + 1].val++;
    } else {
      store[i + 1].val = 1;
      store[i + 1].prev = i;
      store[store[i].next].prev = i + 1;
      store[i + 1].next = store[i].next;
      store[i].next = i + 1;
    }

    store[i].val--;
    if (store[i].val == 0) remove(i);
  }

  void dec(const int i) {
    if (store.count(i - 1)) {
      store[i - 1].val++;
    } else {
      store[i - 1].val = 1;
      store[store[i].prev].next = i - 1;
      store[i - 1].prev = store[i].prev;
      store[i].prev = i - 1;
      store[i - 1].next = i;
    }

    store[i].val--;
    if (store[i].val == 0) remove(i);
  }
};

class AllOne {
  unordered_map<int, unordered_set<string>> count_strs;
  unordered_map<string, int> str_count;
  Ordering ordering;

 public:
  AllOne() { count_strs[0].emplace(""); }

  void inc(const string key) {
    const int prev_count = str_count[key];
    ordering.inc(prev_count);

    if (prev_count == 0) {
      count_strs[1].emplace(key);
      str_count[key] = 1;
    } else {
      const int prev_count = str_count[key];
      count_strs[prev_count].erase(key);
      count_strs[prev_count + 1].emplace(key);
      str_count[key]++;
    }
  }

  void dec(const string key) {
    const int prev_count = str_count[key];
    ordering.dec(prev_count);

    if (prev_count == 1) {
      count_strs[1].erase(key);
      str_count.erase(key);
    } else {
      count_strs[prev_count].erase(key);
      count_strs[prev_count - 1].emplace(key);
      str_count[key]--;
    }
  }

  string getMaxKey() { return *count_strs[ordering.max_key()].begin(); }
  string getMinKey() { return *count_strs[ordering.min_key()].begin(); }
};
