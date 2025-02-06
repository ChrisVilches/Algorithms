class Solution {
    fun isPowerOfTwo(n: Int): Boolean {
        if (n < 1) return false

        return Math.abs(n).countOneBits() == 1
    }
}
