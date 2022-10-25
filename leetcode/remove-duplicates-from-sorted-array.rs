impl Solution {
  pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
    let mut k = 1;

    for i in 1..nums.len() {
      if nums[i] != nums[i - 1] {
        nums[k] = nums[i];
        k += 1;
      }
    }

    k as i32
  }
}
