#pragma once

#include <raylib/raylib.h>
#include <cstdio>

#include "globals.hpp"

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

  void DrawBox(){
    CalculateVertices();
    BeginTextureMode(frameBuffer);

    for (int i = 0; i < 4; i++){
      DrawLineEx(graphVertices[i%4], graphVertices[(i+1)%4], 3.0f, RAYWHITE);
    }

    EndTextureMode();
  }

  void SetOrigin(const int x, const int y){
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

  void Draw(const int x, const int y){
    DrawBox();
    SetOrigin(x, y);
    DrawAxis();
    DrawNumber();
  }

};
