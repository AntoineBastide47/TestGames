//
// Player.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef PADDLE_H
#define PADDLE_H

#include <Engine2D/Entity2D.h>

using Engine2D::Rendering::Texture2D;

class Paddle : public Engine2D::Entity2D {
  public:
    explicit Paddle(const std::string &name) : Entity2D(name) {}

    void OnInitialize() override;
};

#endif //PADDLE_H
