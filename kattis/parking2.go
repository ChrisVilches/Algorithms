package main

import (
	"fmt"
	"sort"
)

func solve() {
	var N int
	fmt.Scan(&N)

	positions := []int{}

	for i := 0; i < N; i++ {
		var x int
		fmt.Scan(&x)
		positions = append(positions, x)
	}

	sort.Ints(positions)

	total := 0

	for i := 0; i < len(positions)-1; i++ {
		total += positions[i+1] - positions[i]
	}

	fmt.Println(total * 2)
}

func main() {
	var T int
	fmt.Scan(&T)

	for i := 0; i < T; i++ {
		solve()
	}
}
