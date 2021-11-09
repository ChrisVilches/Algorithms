fun main() {
  var a:String = readLine()!!
  var b:String = readLine()!!

  var num1 = a.toBigInteger()
  var num2 = b.toBigInteger()

  println(num1.add(num2))
}
