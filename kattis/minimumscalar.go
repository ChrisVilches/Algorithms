package main

import (
	"fmt"
	"sort"
)

func main() {
	var n, T int

	fmt.Scan(&T)

	for t := 0; t < T; t++ {
		fmt.Scan(&n)

		v := make([]int, n)
		u := make([]int, n)

		for i := 0; i < n; i++ {
			fmt.Scan(&v[i])
		}

		for i := 0; i < n; i++ {
			fmt.Scan(&u[i])
		}

		sort.Ints(v)
		sort.Sort(sort.Reverse(sort.IntSlice(u)))

		sum := 0

		for i := 0; i < n; i++ {
			sum += v[i] * u[i]
		}

		fmt.Printf("Case #%d: %d\n", t+1, sum)
	}
}
