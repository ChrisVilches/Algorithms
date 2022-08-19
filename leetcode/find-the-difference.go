package main

func findTheDifference(s string, t string) byte {

	sMap := make(map[byte]int)
	tMap := make(map[byte]int)

	for _, c := range []byte(s) {
		sMap[c]++
	}

	for _, c := range []byte(t) {
		tMap[c]++
	}

	for c, count := range tMap {
		if sMap[c] != count {
			return c
		}
	}

	return '*'

}
