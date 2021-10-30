n = STDIN.gets.to_i

def one_digit?(n)
  n.to_s.count('0123456789') == 1
end

def multiply(n)
  result = 1
  n.to_s.each_char do |d|
    next if d == "0"
    result *= d.to_i
  end
  result
end

while !one_digit?(n)
  n = multiply(n)
end

puts n
