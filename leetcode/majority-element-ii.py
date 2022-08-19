from typing import List


class Solution:
    def majorityElement(self, nums: List[int]) -> List[int]:
        freq = {}

        for val in nums:
            if val not in freq:
                freq[val] = 1
            else:
                freq[val] += 1

        res = []

        for key, f in freq.items():
            if f > len(nums) // 3:
                res.append(key)

        return res
