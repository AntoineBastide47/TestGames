//
// Brick.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef BRICK_H
#define BRICK_H

#include <Engine2D/Behaviour.hpp>
#include "Brick.gen.hpp"

class Brick final : public Engine2D::Behaviour {
  SERIALIZE_BRICK
  public:
    int lives = 0;
    bool isSolid = false;

    void OnInitialize() override;
    void OnCollisionEnter2D(const Engine2D::Physics::Collider2D *collider) override;

    static glm::vec4 GetColor(bool isSolid, int lives);
};

#endif //BRICK_H
