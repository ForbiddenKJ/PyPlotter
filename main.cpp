#include <raylib/raylib.h>
#include <iostream>
#include <math.h>
#include <vector>

Color BACKGROUND = {28, 28, 28, 0};

class PyPlotter{
public:
  void StartWindow(const char* WINDOWNAME, const int SCREENWIDTH, const int SCREENHEIGHT){
    InitWindow(SCREENWIDTH, SCREENHEIGHT, WINDOWNAME);
  }

  std::vector<Vector2> CalculatePoints(int min, int max){
    std::vector<Vector2> points;
    float y;
    float x;
    for (float i = min; i < max; i++){
      x = i;
      y = -pow(x,2);

      x += 40;
      y += 25;

      points.push_back((Vector2){x*10, y*10});
    }

    return points;
  }

  // NOTE: Must be called after BeginDrawing(); and Before EndDrawing();
  void PlotPoints(std::vector<Vector2> points){
    for (int i = 0; i < points.size()-1; i++){
      DrawLineEx(points[i], points[i+1], 3.0f, RAYWHITE);
    }
  }

};

int main(){
  InitWindow(800, 500, "Hello World");

  SetTargetFPS(60);

  PyPlotter plotter;
  std::vector<Vector2> points = plotter.CalculatePoints(-10, 10);

  // Camera2D camera = { 0 };
  // camera.target = (Vector2){0.0f, 0.0f};

  while (!WindowShouldClose()){
    // if (IsKeyDown(KEY_RIGHT)) camera.target.y -= 20;
    // std::cout << camera.target.y << std::endl;
    BeginDrawing();
    ClearBackground(BACKGROUND);
    // BeginMode2D(camera);

    // EndMode2D();
    plotter.PlotPoints(points);
    EndDrawing();
  }

  CloseWindow();
}
