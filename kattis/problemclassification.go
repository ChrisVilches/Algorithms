package main

import (
	"fmt"
	"io"
	"sort"
)

func main() {
	var n int
	fmt.Scan(&n)

	categories := make([]string, n)
	words := make(map[string][]int)

	for i := 0; i < n; i++ {
		fmt.Scan(&categories[i])

		var m int
		fmt.Scan(&m)

		for j := 0; j < m; j++ {
			var word string
			fmt.Scan(&word)
			words[word] = append(words[word], i)
		}
	}

	freqs := make(map[int]int)
	maxVal := 0

	for {
		var word string
		_, err := fmt.Scan(&word)

		if err == io.EOF {
			break
		}

		if cats, ok := words[word]; ok {
			for _, cat := range cats {
				freqs[cat]++
				if freqs[cat] > maxVal {
					maxVal = freqs[cat]
				}
			}
		}
	}

	ans := []string{}

	for i, catName := range categories {
		if freqs[i] == maxVal {
			ans = append(ans, catName)
		}
	}

	sort.Strings(ans)

	for _, s := range ans {
		fmt.Println(s)
	}
}
