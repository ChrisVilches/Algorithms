import java.math.BigInteger

fun factorial(n:Int): BigInteger{
  var total = BigInteger.valueOf(1)

  for(i in 1..n){
    total = total.multiply(BigInteger.valueOf(i.toLong()))
  }

  return total
}

fun solve(){
  var n:Int = readLine()!!.toInt()
  println(factorial(n))
}

fun main(vararg args: String) {
  var tests:Int = readLine()!!.toInt()
  
  while(tests-- > 0) solve()
}
