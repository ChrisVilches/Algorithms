package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func hasCycle(head *ListNode) bool {
	visited := make(map[*ListNode]struct{})

	for head != nil {
		_, ok := visited[head]

		if ok {
			return true
		}

		visited[head] = struct{}{}

		head = head.Next
	}

	return false
}
