#include <cmath>
#include <cstdio>
#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <pybind11/pybind11.h>
#include <GLFW/glfw3.h>

#define LOG(x) std::cout << x << std::endl

namespace py = pybind11;

Color BACKGROUND = {28, 28, 28, 0};
RenderTexture frameBuffer;

class GraphBox{
private:
  Vector2 graphBoxPosition;
  Vector2 graphBoxSize;
  bool originSet;

  void CalculateVertices(){
    graphVertices[0] = (Vector2){graphBoxPosition.x, graphBoxPosition.y};
    graphVertices[1] = (Vector2){graphBoxPosition.x+graphBoxSize.x, graphBoxPosition.y};
    graphVertices[2] = (Vector2){graphBoxPosition.x+graphBoxSize.x, graphBoxPosition.y-graphBoxSize.y};
    graphVertices[3] = (Vector2){graphBoxPosition.x, graphBoxPosition.y-graphBoxSize.y};
  }

public:
  Vector2 center;
  Vector2 origin;

  Vector2 graphVertices[4];

  void SetPosition(int x, int y){
    graphBoxPosition = (Vector2){(float)x, (float)y};
  }

  void SetSize(int x, int y){
    graphBoxSize = (Vector2){(float)x, (float)y};
  }

  Vector2 GetPosition(){
    return graphBoxPosition;
  }

  Vector2 GetSize(){
    return graphBoxSize;
  }

  bool InGraphBox(Vector2 point){
    bool pointInGraphBox = (!((point.x+origin.x > GetPosition().x+GetSize().x)
                              || (point.x+origin.x < GetPosition().x)
                              || (point.y+origin.y < GetPosition().y-GetSize().y)
                              || (point.y+origin.y > GetPosition().y)));

    return pointInGraphBox;
  }


  void Draw(){
    CalculateVertices();
    BeginTextureMode(frameBuffer);

    for (int i = 0; i < 4; i++){
      DrawLineEx(graphVertices[i%4], graphVertices[(i+1)%4], 3.0f, RAYWHITE);
    }

    EndTextureMode();
  }

  void SetOrigin(int x, int y){
    if (!originSet) originSet = true;

    center = {GetPosition().x+(GetSize().x/2),
             GetPosition().y-(GetSize().y/2)};

    if (InGraphBox((Vector2){center.x + x, center.y - y})){
        origin = (Vector2){center.x + x, center.y - y};
    }

  }

  void DrawAxis(){
    if (!originSet) return;

    BeginTextureMode(frameBuffer);
    DrawLineEx((Vector2){graphVertices[0].x, origin.y}, (Vector2){graphVertices[1].x, origin.y}, 1.0f, RAYWHITE);
    DrawLineEx((Vector2){origin.x, graphVertices[0].y}, (Vector2){origin.x, graphVertices[3].y}, 1.0f, RAYWHITE);
    EndTextureMode();
  }

  void DrawNumber(){
    if (!originSet) return;

    int fontSize = 10;
    int textOffset = 2;

    int originSize = MeasureText("0", 10);

    char text[4][32];
    int textSize[4];

    sprintf(text[0], "%i", (int)-GetSize().x);
    sprintf(text[1], "%i", (int)GetSize().x);
    sprintf(text[2], "%i", (int)-GetSize().y);
    sprintf(text[3], "%i", (int)GetSize().y);

    for (int i = 0; i < 4; i++) textSize[i] = MeasureText(text[i], fontSize);

    BeginTextureMode(frameBuffer);
    DrawText("0", (origin.x-originSize)-textOffset, origin.y+textOffset,fontSize, RAYWHITE);

    DrawText(text[0], graphVertices[0].x+textOffset, origin.y+textOffset, fontSize, RAYWHITE);
    DrawText(text[1], (graphVertices[1].x-textSize[1])-textOffset, origin.y+textOffset, fontSize, RAYWHITE);
    DrawText(text[2], (origin.x-textSize[2])-textOffset, (graphVertices[0].y-textOffset)-(fontSize-textOffset), fontSize, RAYWHITE);
    DrawText(text[3], (origin.x-textSize[3])-textOffset, graphVertices[3].y+textOffset, fontSize, RAYWHITE);

    EndTextureMode();
  }

};

class Graph : public GraphBox{
private:
  std::vector<Vector2> points;

public:

  Graph(int posX, int posY, int sizeX, int sizeY){
    SetPosition(posX, posY);
    SetSize(sizeX, sizeY);
  }


  void DrawPoint(Vector2 start, Vector2 end, float thickness = 3.0f, Color color = RAYWHITE){
    BeginTextureMode(frameBuffer);
    DrawLineEx((Vector2){start.x+GetPosition().x, start.y+GetPosition().y},
              (Vector2){end.x+GetPosition().x, end.y+GetPosition().y},
              thickness,
              color);
    EndTextureMode();
  }

  void DrawAroundOrigin(Vector2 start, Vector2 end, float thickness = 3.0f, Color color = RAYWHITE){
    BeginTextureMode(frameBuffer);
    DrawLineEx((Vector2){start.x+origin.x, start.y+origin.y},
              (Vector2){end.x+origin.x, end.y+origin.y},
              thickness,
              color);
    EndTextureMode();
  }

  void Calculate(int range_start, int range_end){

    points.empty();

    if (range_start == range_end) return;

    int step;

    if (range_start < range_end) step = 1;
    if (range_start > range_end) step = -1;

    for (int i = range_start; i != range_end; i+=step){
      float x = i;
      float y = -(pow(x,2)-100);

      points.push_back((Vector2){x, y});
    }

  }

  void DrawPoints(){
    for (int i = 0; i < (int)points.size()-1; i++){

      if (InGraphBox(points[i]) && InGraphBox(points[i+1])){
        DrawAroundOrigin(points[i], points[i+1], 3.0f, BLUE);
      }

    }

  }

};

class PyPlotter{
public:

  PyPlotter(const char* WINDOWNAME, const int SCREENWIDTH, const int SCREENHEIGHT){

    if (glfwInit())
    {
      InitWindow(SCREENWIDTH, SCREENHEIGHT, WINDOWNAME);
      SetTargetFPS(60);

      frameBuffer = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    }

  }

  void MainLoop(){
    Rectangle source = {0, 0, (float)GetScreenWidth(), (float)-GetScreenHeight()};
    Rectangle dest = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
    while (!WindowShouldClose()){
      BeginDrawing();
      ClearBackground(BACKGROUND);
      DrawTexturePro(frameBuffer.texture, source, dest, Vector2Zero(), 0, WHITE);
      EndDrawing();
    }

    CloseWindow();

  }

};


PYBIND11_MODULE(PyPlotter, m){
  py::class_<PyPlotter>(m, "PyPlotter")
    .def(py::init<const char*, const int, const int>())
    .def("main_loop", &PyPlotter::MainLoop);

  py::class_<Graph>(m, "Graph")
    .def(py::init<const int, const int, const int, const int>())
    .def("draw", &Graph::Draw)
    .def("set_origin", &Graph::SetOrigin)
    .def("draw_axis", &Graph::DrawAxis)
    .def("draw_number", &Graph::DrawNumber)
    .def("calculate", &Graph::Calculate)
    .def("draw_points", &Graph::DrawPoints);
}
