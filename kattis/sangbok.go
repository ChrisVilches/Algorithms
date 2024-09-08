package main

import (
	"fmt"
	"sort"
)

func main() {
	var t, n int
	fmt.Scan(&t, &n)

	t *= 60
	nums := make([]int, n)
	for i := range nums {
		fmt.Scan(&nums[i])
	}

	sort.Ints(nums)

	ans := 0

	for _, x := range nums {
		if x > t {
			break
		}

		ans += x
		t -= x
	}

	fmt.Println(ans)
}
