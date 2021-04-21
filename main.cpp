#include <raylib/raylib.h>
#include <iostream>
#include <math.h>
#include <vector>

#define log(x) std::cout << x << std::endl

Color BACKGROUND = {28, 28, 28, 0};

class Graph{
public:
  Vector2 position = {0.0f, 0.0f};
  std::vector<Vector2> points;

  Vector2 origin = {0.0f, 0.0f};

  void DrawGraph(){
    CalculatePoints(-10, 6);
    DrawGraphBox();
    PlotPoints();
  }

private:
  Vector2 graphDimention = {0.0f, 0.0f};
  float lowestY = 0.0f;
  float highestY = 0.0f;

  void PlotPoints(){
    BeginDrawing();
    for (int i = 0; i < (int)points.size()-1; i++){
      DrawLineEx(points[i], points[i+1], 2.0f, RAYWHITE);
    }
    EndDrawing();

  }

  void CalculatePoints(int minX, int maxX, int step = 1, int yCap = 0){
    points.clear();

    bool boundsDefined = false;

    for (int i = minX; i < maxX; i+=step){
      float x = i;
      float y = -(pow(2,x)); // TODO: Customise Equation

      Vector2 pointPosition = {(x*10)+position.x, (y*10)+position.y};

      if (!boundsDefined){
        highestY = pointPosition.y;
        lowestY = pointPosition.y;

        boundsDefined = true;
      }

      if (pointPosition.y > highestY) highestY = pointPosition.y;
      if (pointPosition.y < lowestY) lowestY = pointPosition.y;

      if (!(yCap && pointPosition.y < yCap)){
        points.push_back(pointPosition);
      }

    }

    graphDimention.x = points.back().x - points.front().x;
    graphDimention.y = highestY - lowestY;

  }

  void DrawGraphBox(){
    BeginDrawing();

    Rectangle graphOutline = {points.front().x, position.y-graphDimention.y, graphDimention.x, graphDimention.y};

    DrawRectangleLinesEx(graphOutline, 3.0f, RAYWHITE);

    EndDrawing();
  }
};

class PyPlotter{
public:

  void StartWindow(const char* WINDOWNAME, const int SCREENWIDTH, const int SCREENHEIGHT){
    InitWindow(SCREENWIDTH, SCREENHEIGHT, WINDOWNAME);
    SetTargetFPS(60);

    BeginDrawing();
    ClearBackground(BACKGROUND);
    EndDrawing();
  }

  void KeepWindowAlive(){
    while (!WindowShouldClose()){
      BeginDrawing();
      EndDrawing();
    }

    CloseWindow();
  }

};

int main(){
  PyPlotter plotter;

  plotter.StartWindow("Graph: 2^x", 800, 400);

  Graph basicGraph;

  basicGraph.position = {400, 380};
  basicGraph.DrawGraph();
  // std::cout << basicGraph.points[0].x << " " << basicGraph.points[0].y << std::endl;


  plotter.KeepWindowAlive();

  return 0;
}
