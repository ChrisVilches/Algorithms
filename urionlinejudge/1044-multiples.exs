defmodule Solve do
  def read_ints do
    IO.gets("") |> String.split() |> Enum.map(&String.to_integer/1)
  end

  def solve(a, b) when a < b, do: solve(b, a)

  def solve(a, b) do
    if Integer.mod(a, b) == 0 do
      IO.puts("Sao Multiplos")
    else
      IO.puts("Nao sao Multiplos")
    end
  end
end

[a, b] = Solve.read_ints()
Solve.solve(a, b)
