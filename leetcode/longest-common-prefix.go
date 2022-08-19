package main

func allSameChar(strs []string, idx int) bool {
	c := strs[0][idx]

	for _, str := range strs {
		if str[idx] != c {
			return false
		}
	}
	return true
}

func longestCommonPrefix(strs []string) string {

	n := 1 << 30

	for _, str := range strs {
		if len(str) < n {
			n = len(str)
		}
	}

	result := ""

	for i := 0; i < n; i++ {
		if !allSameChar(strs, i) {
			break
		}

		result = result + string(strs[0][i])

	}

	return result
}
