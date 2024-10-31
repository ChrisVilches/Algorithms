package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)

	curr := 1
	ok := true

	for i := 0; i < n; i++ {
		var x int
		fmt.Scan(&x)

		for ; curr < x; curr++ {
			ok = false
			fmt.Println(curr)
		}

		curr = x + 1
	}

	if ok {
		fmt.Println("good job")
	}
}
