package main

import (
	"fmt"
	"strings"
)

func main() {
	var s string
	var N int

	fmt.Scan(&s)
	fmt.Scan(&N)

	fmt.Println(strings.Repeat(s, N))
}
