//
// Player.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef PLAYER_H
#define PLAYER_H

#include <2D/Entity2D.h>
#include <2D/Rendering/Texture2D.h>
#include <Input/Keyboard.h>

using Engine2D::Rendering::Texture2D;

class Player : public Engine2D::Entity2D {
  public:
    Player(const std::string &name, Entity2D *parent, Texture2D *texture)
      : Entity2D(name, parent, texture) {}

    void Initialize() override;

    void MoveLeft(Engine::Input::KeyboardContext context);
    void MoveRight(Engine::Input::KeyboardContext context);
};

#endif //PLAYER_H
