gets

possible = gets.scan(/\d+/).map(&:to_i).max == gets.scan(/\d+/).map(&:to_i).max

puts possible ? "possible" : "impossible"
