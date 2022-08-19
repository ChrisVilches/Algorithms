package main

func reverseString(s []byte) {
	for i := 0; i < len(s)/2; i++ {
		temp := s[len(s)-i-1]
		s[len(s)-i-1] = s[i]
		s[i] = temp
	}
}
