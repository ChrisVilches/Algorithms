fun main() {
  var n: Int
  var c: Int = 0
  var cases: Int
  var stalls: ArrayList<Int> = arrayListOf<Int>()

  fun possible(dist: Int): Boolean{
    var prev = stalls[0]
    var allocated = 1
    for(i in 1..stalls.size-1){
      if(stalls[i] - prev >= dist){
        allocated++
        prev = stalls[i]
      }

      if(allocated >= c) return true
    }
    return false
  }

  fun solve(){
    val input = readLine()!!.split(" ").map { it.toInt() }
    n = input[0]
    c = input[1]

    stalls = arrayListOf<Int>()

    repeat(n){
      stalls.add(readLine()!!.toInt())
    }
    stalls.sort()

    var left = 1
    var right = 1000000000
    var value = -1

    while(left < right){
      var mid = (left + right)/2

      if(possible(mid)){
        value = mid
        left = mid + 1
      } else {
        right = mid
      }
    }

    println(value)
  }

  cases = readLine()!!.toInt()
  while(cases-- > 0)
    solve();
}
