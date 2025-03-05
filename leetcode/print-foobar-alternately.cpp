#include <bits/stdc++.h>
using namespace std;

class FooBar {
 private:
  int n;
  binary_semaphore s1{1}, s2{0};

 public:
  FooBar(const int n) : n(n) {}

  void foo(const function<void()> printFoo) {
    for (int i = 0; i < n; i++) {
      s1.acquire();
      printFoo();
      s2.release();
    }
  }

  void bar(const function<void()> printBar) {
    for (int i = 0; i < n; i++) {
      s2.acquire();
      printBar();
      s1.release();
    }
  }
};
