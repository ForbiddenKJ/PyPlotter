#include <raylib/raylib.h>
#include <iostream>
#include <math.h>
#include <vector>

#define LOG(x) std::cout << x << std::endl

Color BACKGROUND = {28, 28, 28, 0};

class Graph{
public:
  Vector2 position = {0.0f, 0.0f};
  std::vector<Vector2> points;

  Vector2 origin = {0.0f, 0.0f};

  void DrawGraph(){
    CalculatePoints(-5, 5);
    PlotPoints();
    DrawGraphBox();

  }

private:
  Vector2 graphDimention = {0.0f, 0.0f};
  float lowestY = 0.0f;
  float highestY = 0.0f;

  void PlotPoints(){
    BeginDrawing();
    for (int i = 0; i < (int)points.size()-1; i++){
      DrawLineEx(points[i], points[i+1], 2.0f, BLUE);
    }
    EndDrawing();

  }

  void CalculatePoints(int minX, int maxX, int step = 1, int yCap = 0){
    points.clear();

    bool boundsDefined = false;

    for (int i = minX; i < maxX+1; i+=step){
      float x = i;
      float y = -(pow(x,2)+16*x+2); // TODO: Customise Equation

      Vector2 pointPosition = {(x*10)+position.x, (y*10)+position.y};

      if (!boundsDefined){
        highestY = pointPosition.y;
        lowestY = pointPosition.y;

        boundsDefined = true;
      }

      if (pointPosition.y < highestY) highestY = pointPosition.y;
      if (pointPosition.y > lowestY) lowestY = pointPosition.y;

      if (!(yCap && pointPosition.y < yCap)){
        points.push_back(pointPosition);
      }

    }

    graphDimention.x = points.back().x - points.front().x;
    graphDimention.y = highestY - lowestY;

  }

  void DrawGraphBox(){
    BeginDrawing();

    Vector2 graphPoint[4] = {(Vector2){points.front().x, lowestY},
                            (Vector2){points.front().x+graphDimention.x, lowestY},
                            (Vector2){points.front().x+graphDimention.x, highestY},
                            (Vector2){points.front().x, highestY}};

    for (int i = 0; i < 4; i++){
      DrawLineEx(graphPoint[i%4], graphPoint[(i+1)%4], 3.0f, RAYWHITE);
    }

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

  plotter.StartWindow("Graph: 2^x", 800, 500);

  Graph basicGraph;

  basicGraph.position = {400, 250};
  basicGraph.DrawGraph();

  plotter.KeepWindowAlive();

  return 0;
}
