package main

import (
	"fmt"
)

func main() {
	var N int

	fmt.Scan(&N)

	total := 0

	for i := 0; i < N; i++ {
		var num int
		fmt.Scan(&num)
		total += num
	}

	fmt.Printf("%d\n", total)
}
