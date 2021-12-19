package main

import (
	"fmt"
)

var (
	N     int
	graph [21][21]bool
)

func isWeak(v int) bool {
	for i := 0; i < N; i++ {
		if !graph[v][i] {
			continue
		}

		for j := 0; j < N; j++ {
			if graph[i][j] && graph[j][v] {
				return false
			}
		}
	}

	return true
}

func solve() {
	for i := 0; i < N; i++ {
		for j := 0; j < N; j++ {
			fmt.Scan(&graph[i][j])
		}
	}

	for i := 0; i < N; i++ {
		if isWeak(i) {
			fmt.Printf("%d ", i)
		}
	}

	fmt.Println()
}

func main() {
	for {
		fmt.Scan(&N)
		if N == -1 {
			break
		}

		solve()
	}
}
