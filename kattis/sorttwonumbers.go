package main

import (
	"fmt"
)

func main() {
	var a, b int

	fmt.Scan(&a, &b)

	if a > b {
		a, b = b, a
	}

	fmt.Printf("%d %d\n", a, b)
}
