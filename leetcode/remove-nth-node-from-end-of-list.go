func len(head *ListNode) int {
	if head == nil {
		return 0
	}
	return 1 + len(head.Next)
}

func removeNthFromEnd(head *ListNode, n int) *ListNode {
	n = len(head) - n

	if n == 0 {
		return head.Next
	}

	curr := head

	for i := 0; i < n-1; i++ {
		curr = curr.Next
	}

	curr.Next = curr.Next.Next

	return head
}
