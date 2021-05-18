#pragma once

#include <raylib/raylib.h>
#include "MathParser/include/parser.hpp"
#include <vector>

class GraphLine{
private:
  std::vector<Vector2> points;

public:
  std::vector<Vector2> GetPoints(){ return points; }

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

  }

  void Plot(const float x = .0f, const float y = .0f){ points.push_back((Vector2){x, y}); }
};
