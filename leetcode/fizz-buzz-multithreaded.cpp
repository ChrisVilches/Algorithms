#include <bits/stdc++.h>
using namespace std;

class FizzBuzz {
 private:
  const int n;
  barrier<> barr{4};

 public:
  FizzBuzz(const int n) : n(n) {}

  void fizz(const function<void()> printFizz) {
    for (int i = 1; i <= n; i++) {
      if (i % 3 == 0 && i % 5 != 0) printFizz();
      barr.arrive_and_wait();
    }
  }

  void buzz(const function<void()> printBuzz) {
    for (int i = 1; i <= n; i++) {
      if (i % 3 != 0 && i % 5 == 0) printBuzz();
      barr.arrive_and_wait();
    }
  }

  void fizzbuzz(const function<void()> printFizzBuzz) {
    for (int i = 1; i <= n; i++) {
      if (i % 3 == 0 && i % 5 == 0) printFizzBuzz();
      barr.arrive_and_wait();
    }
  }

  void number(const function<void(int)> printNumber) {
    for (int i = 1; i <= n; i++) {
      if (i % 3 != 0 && i % 5 != 0) printNumber(i);
      barr.arrive_and_wait();
    }
  }
};
