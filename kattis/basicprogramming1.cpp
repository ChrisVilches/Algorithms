#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int A[200020];
int repetition[200020];
int N, t;

void one() { cout << 7 << endl; }

void two() {
  if (A[0] > A[1])
    cout << "Bigger";
  else if (A[0] == A[1])
    cout << "Equal";
  else
    cout << "Smaller";

  cout << endl;
}

void three() {
  vector<int> nums{A[0], A[1], A[2]};
  sort(nums.begin(), nums.end());
  cout << nums[1] << endl;
}

void four() {
  ll accum = 0;
  for (int i = 0; i < N; i++) accum += (ll)A[i];
  cout << accum << endl;
}

void five() {
  ll accum = 0;
  for (int i = 0; i < N; i++)
    if (A[i] % 2 == 0) accum += (ll)A[i];

  cout << accum << endl;
}

void six() {
  for (int i = 0; i < N; i++) {
    printf("%c", (A[i] % 26) + 'a');
  }
  cout << endl;
}

void seven() {
  memset(repetition, 0, sizeof repetition);
  int i = 0;
  while (true) {
    i = A[i];
    repetition[i]++;
    if (repetition[i] > 1) {
      cout << "Cyclic" << endl;
      return;
    }
    if (i < 0 || i >= N) {
      cout << "Out" << endl;
      return;
    }

    if (i == N - 1) {
      cout << "Done" << endl;
      return;
    }
  }
}

int main() {
  cin >> N >> t;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  if (t == 1) one();
  if (t == 2) two();
  if (t == 3) three();
  if (t == 4) four();
  if (t == 5) five();
  if (t == 6) six();
  if (t == 7) seven();
}
