package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func deleteDuplicates(head *ListNode) *ListNode {
	if head == nil {
		return head
	}

	curr := head
	next := curr.Next

	for next != nil {
		if curr.Val != next.Val {
			curr.Next = next
			curr = next
		}

		next = next.Next
	}

	curr.Next = nil

	return head
}
