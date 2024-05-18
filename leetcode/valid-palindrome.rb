def is_palindrome(s)
  s.downcase!
  s.gsub!(/[^a-z0-9]/, '')
  s == s.reverse
end
