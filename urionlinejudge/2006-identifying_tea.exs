{t, _} = IO.gets("") |> Integer.parse()

nums = IO.gets("") |> String.split() |> Enum.map(&String.to_integer/1)

IO.puts(nums |> Enum.count(fn x -> x == t end))
