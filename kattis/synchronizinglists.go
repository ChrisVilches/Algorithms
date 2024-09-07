package main

import (
	"fmt"
	"sort"
)

func toSorted(arr []int) []int {
	a := make([]int, len(arr))
	copy(a, arr)
	sort.Ints(a)
	return a
}

func main() {
	var n int

	for {
		fmt.Scan(&n)

		if n == 0 {
			break
		}

		a := make([]int, n)
		b := make([]int, n)

		for i := 0; i < n; i++ {
			fmt.Scan(&a[i])
		}

		for i := 0; i < n; i++ {
			fmt.Scan(&b[i])
		}

		aSorted := toSorted(a)
		bSorted := toSorted(b)

		aMap := make(map[int]int)
		bMap := make(map[int]int)

		for i := 0; i < n; i++ {
			aMap[aSorted[i]] = i
			bMap[i] = bSorted[i]
		}

		for i := 0; i < n; i++ {
			aVal := a[i]
			idx := aMap[aVal]
			bVal := bMap[idx]
			fmt.Println(bVal)
		}

		fmt.Println()
	}
}
