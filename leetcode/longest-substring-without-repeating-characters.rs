use std::cmp;
use std::collections::HashSet;

impl Solution {
  pub fn length_of_longest_substring(original: String) -> i32 {
    let s: Vec<char> = original.chars().collect();

    let mut present = HashSet::new();

    let mut result = 0;

    let mut i = 0;
    let mut j = 0;
    while i < s.len() {
      let c = s[i];

      while present.contains(&c) {
        present.remove(&s[j]);
        j += 1;
      }

      present.insert(c);
      result = cmp::max(result, i - j + 1);

      i += 1;
    }

    result as i32
  }
}
