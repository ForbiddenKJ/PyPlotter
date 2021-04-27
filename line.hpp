#include <raylib/raylib.h>
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

class Line{
private:
  Vector2 points[2];

public:
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

Vector2 intersect(Line line1, Line line2){
  float x_intersect = (line2.y_intercept() - line1.y_intercept()) / (line1.gradient() - line2.gradient());
  float y_intersect = line1.gradient() * x_intersect + line1.y_intercept();

  return (Vector2){x_intersect, y_intersect};
}
