from PyPlotter import Plotter, Graph

plotter = Plotter("Graph", 800, 500)
graph = Graph(400, 250, 100, 200)

graph.draw()
graph.set_origin(0, 0)
graph.draw_axis()
graph.draw_number()
graph.calculate(-100, 100, "x^2")
graph.draw_points()

plotter.main_loop()
