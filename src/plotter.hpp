#pragma once

#include <GLFW/glfw3.h>
#include <raylib/raylib.h>
#include <raylib/raymath.h>

#include "globals.hpp"

class Plotter{
public:

  Plotter(const char* WINDOWNAME, const int SCREENWIDTH, const int SCREENHEIGHT){

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
