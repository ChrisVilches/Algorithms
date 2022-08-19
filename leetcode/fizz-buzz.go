package main

import "fmt"

func fizzBuzz(n int) []string {
	var res []string

	for i := 1; i <= n; i++ {
		var s string

		if i%3 == 0 {
			s += "Fizz"
		}

		if i%5 == 0 {
			s += "Buzz"
		}

		if len(s) == 0 {
			s = fmt.Sprint(i)
		}

		res = append(res, s)
	}

	return res
}
