class Solution {
    fun addDigits(num: Int): Int {
        var v = num

        while (v >= 10) {
            v = v.toString().map(Char::digitToInt).sum()
        }

        return v
    }
}
