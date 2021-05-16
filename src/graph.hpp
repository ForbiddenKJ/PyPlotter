#pragma once

#include <raylib/raylib.h>
#include <vector>
#include <cmath>

#include "globals.hpp"
#include "graphbox.hpp"
#include "MathParser/include/parser.hpp"

class Graph : public GraphBox{
private:
  std::vector<Vector2> points;

  void DrawPoints(){
    for (int i = 0; i < (int)points.size()-1; i++){
      if (InGraphBox(points[i]) && InGraphBox(points[i+1])){
        DrawAroundOrigin(points[i], points[i+1], 3.0f, BLUE);
      }

    }

  }


public:

  Graph(int posX, int posY, int sizeX, int sizeY){
    SetPosition(posX, posY);
    SetSize(sizeX, sizeY);
  }


  void DrawPoint(const Vector2 start, const Vector2 end, const float thickness = 3.0f, const Color color = RAYWHITE){
    BeginTextureMode(frameBuffer);
    DrawLineEx((Vector2){start.x+GetPosition().x, start.y+GetPosition().y},
              (Vector2){end.x+GetPosition().x, end.y+GetPosition().y},
              thickness,
              color);
    EndTextureMode();
  }

  void DrawAroundOrigin(const Vector2 start, const Vector2 end, const float thickness = 3.0f, const Color color = RAYWHITE){
    BeginTextureMode(frameBuffer);
    DrawLineEx((Vector2){start.x+origin.x, start.y+origin.y},
              (Vector2){end.x+origin.x, end.y+origin.y},
              thickness,
              color);
    EndTextureMode();
  }

  void Calculate(const int range_start, const int range_end, const std::string expr){

    points.empty();

    if (range_start == range_end) return;

    int step;

    if (range_start < range_end) step = 1;
    if (range_start > range_end) step = -1;

    MathParser parser;

    mp_RPN rpn = parser.reversePolishNotation(expr);

    for (int i = range_start; i != range_end; i+=step){

      float x = i;

      parser.appendVariable("x", (double)x);

      float y = -((float)parser.eval(rpn));

      points.push_back((Vector2){x, y});
    }

    DrawPoints();

  }

  void Plot(const int range_start, const int range_end, const std::string expr){
    Calculate(range_start, range_end, expr);
    DrawPoints();
  }

};
