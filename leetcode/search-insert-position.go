package main

func searchInsert(nums []int, target int) int {
	lo := 0
	hi := len(nums)

	for lo < hi {
		mid := (lo + hi) / 2

		if target > nums[mid] {
			lo = mid + 1
		} else {
			hi = mid
		}
	}

	return lo
}
