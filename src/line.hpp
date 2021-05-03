#pragma once

#include <cmath>
#include <raylib/raylib.h>
#include <math.h>
#include <iostream>

class Line{

public:
  Vector2 points[2];

  void SetPoints(Vector2 point1, Vector2 point2){
    points[0] = point1;
    points[1] = point2;
  }

  Vector2 diff(){
    return (Vector2){points[1].x - points[0].x, points[1].y - points[0].y};
  }

  float gradient(){
    return diff().y/diff().x;
  }

  float y_intercept(){
    return points[0].y-points[0].x*gradient();
  }

  float x_intercept(){
    return points[0].x-points[0].y/gradient();
  }
};

bool doesIntersect(Line line1, Line line2){
  return abs(line1.gradient()-line2.gradient());
}

Vector2 intersect(Line line1, Line line2){
  float l1_gradient = line1.gradient();
  float l2_gradient = line2.gradient();

  if (line1.gradient() == INFINITY || line1.gradient() == -INFINITY){
    line1.points[0].x += 0.0005;
    return intersect(line1, line2);
  }

  if (line2.gradient() == INFINITY || line2.gradient() == -INFINITY){
    line2.points[0].x += 0.0005;
    return intersect(line1, line2);
  }

  float x_intersect = (line2.y_intercept() - line1.y_intercept()) / (l1_gradient - l2_gradient);
  float y_intersect = l1_gradient * x_intersect + line1.y_intercept();

  return (Vector2){x_intersect, y_intersect};
}
