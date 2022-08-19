package main

func containsNearbyDuplicate(nums []int, k int) bool {

	idx := make(map[int]int)

	for i, n := range nums {

		prevIdx, present := idx[n]

		if present && i-prevIdx <= k {
			return true
		}

		idx[n] = i

	}

	return false

}
