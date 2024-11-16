//
// Player.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef PLAYER_H
#define PLAYER_H
#include <2D/Entity2D.h>

class Player : public Engine2D::Entity2D {
  public:
    Player(const std::string &name, Entity2D *parent, Engine2D::Rendering::Texture2D *texture)
      : Entity2D(name, parent, texture) {}

    void Initialize() override;
    void ProcessInput() override;
};

#endif //PLAYER_H
