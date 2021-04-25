#include <raylib/raylib.h>
#include <iostream>
#include <math.h>
#include <vector>

#define LOG(x) std::cout << x << std::endl

Color BACKGROUND = {28, 28, 28, 0};

class GraphBox{
private:
  Vector2 graphBoxPosition;
  Vector2 graphBoxSize;

  void CalculateVertices(){
    graphVertices[0] = (Vector2){graphBoxPosition.x, graphBoxPosition.y};
    graphVertices[1] = (Vector2){graphBoxPosition.x+graphBoxSize.x, graphBoxPosition.y};
    graphVertices[2] = (Vector2){graphBoxPosition.x+graphBoxSize.x, graphBoxPosition.y-graphBoxSize.y};
    graphVertices[3] = (Vector2){graphBoxPosition.x, graphBoxPosition.y-graphBoxSize.y};
  }

public:
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

  void Draw(){
    CalculateVertices();
    BeginDrawing();

    for (int i = 0; i < 4; i++){
      DrawLineEx(graphVertices[i%4], graphVertices[(i+1)%4], 3.0f, RAYWHITE);
    }

    EndDrawing();
  }

};

class Graph : public GraphBox{
private:
  Vector2 center;
  Vector2 origin;

  std::vector<Vector2> points;

public:

  void SetOrigin(Vector2 pos){
    center = {GetPosition().x+(GetSize().x/2),
             GetPosition().y-(GetSize().y/2)};

    origin = (Vector2){center.x + pos.x,
             center.y - pos.y};

  }

  void DrawPoint(Vector2 start, Vector2 end, float thickness = 3.0f, Color color = RAYWHITE){
    BeginDrawing();
    DrawLineEx((Vector2){start.x+GetPosition().x, start.y+GetPosition().y},
              (Vector2){end.x+GetPosition().x, end.y+GetPosition().y},
              thickness,
              color);
  }

  void DrawAroundOrigin(Vector2 start, Vector2 end, float thickness = 3.0f, Color color = RAYWHITE){
    BeginDrawing();
    DrawLineEx((Vector2){start.x+origin.x, start.y+origin.y},
              (Vector2){end.x+origin.x, end.y+origin.y},
              thickness,
              color);
  }

  void Calculate(int range_start, int range_end){

    points.empty();

    if (range_start < range_end){
      for (int i = range_start; i < range_end; i++){
        float x = i;
        float y = -(pow(x,2));

        points.push_back((Vector2){x, y});
      }
    }

    if (range_start > range_end){
      for (int i = range_start; range_start > range_end; i--){
        LOG("Hey");
      }
    }
  }

  void DrawPoints(){
    for (int i = 0; i < (int)points.size()-1; i++){
      DrawAroundOrigin(points[i], points[i+1]);
    }
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

  Graph basicGraphBox;
  basicGraphBox.SetPosition(400, 250);
  basicGraphBox.SetSize(100, 100);

  basicGraphBox.Draw();

  basicGraphBox.SetOrigin((Vector2){0.0f, 0.0f});

  basicGraphBox.Calculate(-100, 100);
  basicGraphBox.DrawPoints();

  plotter.KeepWindowAlive();

  return 0;
}
