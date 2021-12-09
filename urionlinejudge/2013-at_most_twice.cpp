#include <bits/stdc++.h>

using namespace std;

char line[20];
short digits[20];
int length, occurrences[10];

int incorrect_index() {
  memset(occurrences, 0, sizeof occurrences);
  for (int i = 0; i < length; i++)
    if (++occurrences[digits[i]] > 2) return i;
  return -1;
}

void print_result() {
  int i = 0;
  for (; i < length; i++)
    if (digits[i] != 0) break;
  for (; i < length; i++) printf("%d", digits[i]);
  printf("\n");
}

void fix(int i) {
  digits[i]--;
  for (int n = i + 1; n < length; n++) digits[n] = 9;

  while (digits[i] == -1) {
    digits[i] = 9;
    if (i > 0) digits[--i]--;
  }
}

int main() {
  while (scanf("%s", line) == 1) {
    length = strlen(line);
    for (int i = 0; i < length; i++) digits[i] = line[i] - '0';

    while (true) {
      int i = incorrect_index();
      if (i == -1) break;
      fix(i);
    }

    print_result();
  }
}
