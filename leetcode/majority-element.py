from typing import List


class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        freq = {}

        for val in nums:
            if val not in freq:
                freq[val] = 1
            else:
                freq[val] += 1

        for key, f in freq.items():
            if f > len(nums) // 2:
                return key

        return -1
