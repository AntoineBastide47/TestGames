//
// Player.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef PADDLE_H
#define PADDLE_H

#include <2D/Entity2D.h>
#include <2D/Rendering/Texture2D.h>
#include <2D/Physics/Rigidbody2D.h>

using Engine2D::Rendering::Texture2D;

class Paddle : public Engine2D::Entity2D {
  public:
    std::shared_ptr<Engine2D::Physics::Rigidbody2D> rigidbody;

    explicit Paddle(const std::string &name) : Entity2D(name) {}

    void Initialize() override;
};

#endif //PADDLE_H
