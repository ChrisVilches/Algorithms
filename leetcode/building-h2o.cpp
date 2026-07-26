#include <bits/stdc++.h>
using namespace std;

class H2O {
  mutex mtx;
  counting_semaphore<> o_sem{1}, h_sem{2};
  int rem = 3;

  void post_add_atom() {
    lock_guard<mutex> lock(mtx);
    rem--;

    if (rem > 0) return;

    rem = 3;
    o_sem.release();
    h_sem.release(2);
  }

 public:
  void hydrogen(const function<void()> releaseHydrogen) {
    h_sem.acquire();
    releaseHydrogen();
    post_add_atom();
  }

  void oxygen(const function<void()> releaseOxygen) {
    o_sem.acquire();
    releaseOxygen();
    post_add_atom();
  }
};
