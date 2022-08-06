defmodule Area do
  def triangle(base, height) do
    base * height / 2
  end

  def circle(radius) do
    3.14159 * radius * radius
  end

  def trapezium(base1, base2, height) do
    b1 = Kernel.min(base1, base2)
    b2 = Kernel.max(base1, base2)

    rectangle = b1 * height
    triangles = (b2 - b1) * height / 2

    rectangle + triangles
  end

  def rectangle(side) do
    side * side
  end

  def rectangle(side1, side2) do
    side1 * side2
  end
end

[a, b, c] = IO.gets("") |> String.split() |> Enum.map(&String.to_float/1)

labels = [
  "TRIANGULO",
  "CIRCULO",
  "TRAPEZIO",
  "QUADRADO",
  "RETANGULO"
]

areas = [
  Area.triangle(a, c),
  Area.circle(c),
  Area.trapezium(a, b, c),
  Area.rectangle(b),
  Area.rectangle(a, b)
]

for {label, area} <- Enum.zip(labels, areas) do
  IO.puts("#{label}: #{:io_lib.format("~.3f", [area])}")
end
