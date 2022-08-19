package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func removeElements(head *ListNode, val int) *ListNode {
	for head != nil && head.Val == val {
		head = head.Next
	}

	if head == nil {
		return nil
	}

	curr := head

	for curr.Next != nil {
		if curr.Next.Val != val {
			curr = curr.Next
		} else {
			curr.Next = curr.Next.Next
		}
	}

	return head
}
