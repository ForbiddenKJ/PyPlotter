#include <raylib/raylib.h>
#include <iostream>
#include <math.h>
#include <vector>

Color BACKGROUND = {28, 28, 28, 0};

class Graph{
public:
  Vector2 position;
  std::vector<Vector2> points;
  Vector2 graphDimention;

  void DrawGraph(){
    CalculatePoints(-10, 10);
    PlotPoints();
  }

private:
  void PlotPoints(){

    for (int i = 0; i < points.size()-1; i++){
      DrawLineEx(points[i], points[i+1], 4.0f, RAYWHITE);
    }

  }

  void CalculatePoints(int minX, int maxX){
    points.clear();

    for (int i = minX; i < maxX; i++){
      float x = i;
      float y = -pow(2,x); // TODO: Customise Equation

      x += 40;
      y += 25;

      points.push_back((Vector2){x*10, y*10});
    }
  }
};

class PyPlotter{
public:

  void StartWindow(const char* WINDOWNAME, const int SCREENWIDTH, const int SCREENHEIGHT){
    InitWindow(SCREENWIDTH, SCREENHEIGHT, WINDOWNAME);
    SetTargetFPS(60);
  }

};

int main(){
  PyPlotter plotter;

  plotter.StartWindow("Graph: x^2", 800, 500);

  Graph basicGraph;

  while (!WindowShouldClose()){
    BeginDrawing();

    ClearBackground(BACKGROUND);

    basicGraph.DrawGraph();

    EndDrawing();

  }

  CloseWindow();
}
