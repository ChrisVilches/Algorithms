{b, _} = IO.gets("") |> Integer.parse()
{g, _} = IO.gets("") |> Integer.parse()

g = Integer.floor_div(g, 2)
missing = g - b

if missing <= 0 do
  IO.puts("Amelia tem todas bolinhas!")
else
  IO.puts("Faltam #{missing} bolinha(s)")
end
