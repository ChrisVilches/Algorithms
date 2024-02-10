#include <bits/stdc++.h>
using namespace std;

void fft(vector<complex<double>>& seq, const bool inverse) {
  const int n = seq.size();

  if (n == 1) return;

  const double ang = (inverse ? -1 : 1) * M_PI * 2 / n;
  complex<double> w(cos(ang), sin(ang));

  vector<complex<double>> even, odd;

  for (int i = 0; i < n; i += 2) {
    even.push_back(seq[i]);
    odd.push_back(seq[i + 1]);
  }

  fft(even, inverse);
  fft(odd, inverse);

  complex<double> curr_w(1, 0);

  for (int i = 0; i < n / 2; i++) {
    seq[i] = even[i] + odd[i] * curr_w;
    seq[i + (n / 2)] = even[i] - odd[i] * curr_w;
    curr_w *= w;
  }

  if (inverse) {
    for (auto& x : seq) x /= 2;
  }
}

vector<complex<double>> pad_zeros(const vector<complex<double>>& seq, const int n) {
  vector<complex<double>> result(n, 0);
  copy(seq.begin(), seq.end(), result.begin());
  return result;
}

int next_power_2(int x) { return pow(2, ceil(log2(x))); }

vector<complex<double>> convolution(vector<complex<double>> seq1,
                                    vector<complex<double>> seq2) {
  const int final_length = seq1.size() + seq2.size() - 1;
  const int n = next_power_2(final_length);

  seq1 = pad_zeros(seq1, n);
  seq2 = pad_zeros(seq2, n);

  fft(seq1, false);
  fft(seq2, false);
  for (int i = 0; i < (int)seq1.size(); i++) {
    seq1[i] *= seq2[i];
  }
  fft(seq1, true);

  return vector<complex<double>>(seq1.begin(), seq1.begin() + final_length);
}

vector<complex<double>> read(const int n) {
  vector<complex<double>> result(n);
  for (auto& val : result) {
    int x;
    cin >> x;
    val.real(x);
  }
  return result;
}

void solve() {
  int n;
  cin >> n;
  n++;
  const vector<complex<double>> p1 = read(n);
  const vector<complex<double>> p2 = read(n);

  for (const auto x : convolution(p1, p2)) {
    cout << (long long)round(x.real()) << ' ';
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;
  while (t--) solve();
}
