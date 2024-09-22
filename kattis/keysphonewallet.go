package main

import (
	"fmt"
)

func contains(arr []string, item string) bool {
	for _, s := range arr {
		if s == item {
			return true
		}
	}
	return false
}

func main() {
	var n int
	fmt.Scan(&n)

	words := make([]string, n)

	for i := 0; i < n; i++ {
		fmt.Scan(&words[i])
	}

	objects := []string{"keys", "phone", "wallet"}

	forgot := false

	for _, obj := range objects {
		if !contains(words, obj) {
			forgot = true
			fmt.Println(obj)
		}
	}

	if !forgot {
		fmt.Println("ready")
	}
}
