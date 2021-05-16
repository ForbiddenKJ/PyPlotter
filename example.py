from PyPlotter import Plotter, Graph

plotter = Plotter("Graph", 800, 500)
graph = Graph(400, 250, 100, 200)

graph.draw(0, 0)
graph.plot(-100, 100, "x^2")

plotter.main_loop()
