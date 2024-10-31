//
// main.cpp
// main: 
// Author: Antoine Bastide
// Date: 30/10/2024
//

#include "Engine/2D/Game2D.h"

int main() {
  Engine2D::Game2D game_2d { 800, 600, "test" };
  game_2d.Initialize();

  while (game_2d.IsRunning()) {
    game_2d.Render();
  }

  game_2d.Quit();
  return 0;
}
