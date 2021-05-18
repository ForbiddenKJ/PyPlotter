from PyPlotter import Plotter, Graph, Line

plotter = Plotter("Graph", 800, 500)
graph = Graph(400, 250, 100, 200)
line = Line()

line.calculate(-100, 100, "x^2")

graph.draw(0, 0)
graph.draw_line(line)

plotter.main_loop()
