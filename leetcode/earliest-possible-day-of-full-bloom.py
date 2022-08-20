from typing import List


class Solution:
    def earliestFullBloom(self, plantTime: List[int], growTime: List[int]) -> int:
        plants = list(
            map(lambda i: (growTime[i], plantTime[i]), range(len(plantTime))))

        plants.sort(reverse=True)

        res = 0

        plant_time = 0

        for g, p in plants:
            plant_time += p
            res = max(res, plant_time + g)

        return res
