package main

import (
	"fmt"
)

var mapping = map[rune]rune{
	'(': ')',
	'[': ']',
	'{': '}',
}

func valid(s string) bool {
	stack := []rune{'$'}

	for _, c := range s {
		_, isLeft := mapping[c]

		if isLeft {
			stack = append(stack, c)
		} else {
			last := stack[len(stack)-1]

			if mapping[last] == c {
				stack = stack[:len(stack)-1]
			} else {
				return false
			}

		}
	}

	return len(stack) == 1
}

func main() {
	var n int
	var s string

	fmt.Scan(&n)
	fmt.Scan(&s)

	if valid(s) {
		fmt.Println("Valid")
	} else {
		fmt.Println("Invalid")
	}
}
