package main

func containsDuplicate(nums []int) bool {
	var unique = make(map[int]struct{})

	for _, n := range nums {
		_, present := unique[n]

		if present {
			return true
		}

		unique[n] = struct{}{}
	}

	return false
}
