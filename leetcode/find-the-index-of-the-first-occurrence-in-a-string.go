package main

func strStr(haystack string, needle string) int {
	for i := 0; i < len(haystack)-len(needle)+1; i++ {
		slice := haystack[i : i+len(needle)]
		if slice == needle {
			return i
		}
	}

	return -1
}
