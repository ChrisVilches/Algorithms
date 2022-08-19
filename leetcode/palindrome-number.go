package main

import "strconv"

func reverse(s string) string {
	rs := []rune(s)

	for i := 0; i < len(s)/2; i++ {
		temp := rs[len(s)-i-1]
		rs[len(s)-i-1] = rs[i]
		rs[i] = temp
	}

	return string(rs)
}

func isPalindrome(x int) bool {
	strNum := strconv.Itoa(x)

	return strNum == reverse(strNum)
}
