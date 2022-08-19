package main

func merge(nums1 []int, m int, nums2 []int, n int) {
	if n == 0 {
		return
	} else if m == 0 {
		copy(nums1, nums2)
		return
	}

	var result []int

	for i, j := 0, 0; len(result) < n+m; {

		if i == m || (j < n && nums2[j] <= nums1[i]) {
			result = append(result, nums2[j])
			j++
		} else {
			result = append(result, nums1[i])
			i++
		}

	}

	copy(nums1, result)
}
