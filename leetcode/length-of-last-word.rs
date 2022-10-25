impl Solution {
  pub fn length_of_last_word(s: String) -> i32 {
    s.split(' ')
      .filter(|s| !s.trim().is_empty())
      .collect::<Vec<&str>>()
      .last()
      .unwrap()
      .len() as i32
  }
}
