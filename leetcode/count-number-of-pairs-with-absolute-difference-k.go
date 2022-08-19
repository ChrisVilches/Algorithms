package main

func diff(a int, b int) int {
	if a < b {
		return b - a
	} else {
		return a - b
	}
}

func countKDifference(nums []int, k int) int {

	res := 0

	for i := 0; i < len(nums); i++ {
		for j := i + 1; j < len(nums); j++ {
			if diff(nums[i], nums[j]) == k {
				res++
			}
		}
	}

	return res

}
