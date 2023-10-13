def mod_inverse(a, m)
  return 0 if m == 1

  m0 = m
  x = 1
  y = 0

  while a > 1
    q = a / m
    t = m
    m = a % m
    a = t
    t = y
    y = x - (q * y)
    x = t
  end

  x += m0 while x < 0
  x
end

t = $stdin.gets.to_i

t.times do
  a, n, b, m = $stdin.gets.split.collect(&:to_i)
  k = n * m

  inv1 = mod_inverse(m, n)
  inv2 = mod_inverse(n, m)

  x = (a * m * inv1) + (b * n * inv2)
  x %= k
  puts "#{x} #{k}"
end
