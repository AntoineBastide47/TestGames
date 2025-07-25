//
// Ball.h
// Author: Antoine Bastide
// Date: 20/11/2024
//

#ifndef BALL_H
#define BALL_H

#include <Engine2D/Behaviour.hpp>
#include <Engine2D/Physics/Rigidbody2D.hpp>
#include "Ball.gen.hpp"

namespace Engine2D {
  class ParticleSystem2D;
}

class Ball final : public Engine2D::Behaviour {
  SERIALIZE_BALL
  public:
    inline static glm::vec2 INITIAL_VELOCITY = glm::vec2(3, 12) * 100.0f;
    bool stuck = true;

    Ball();

    Engine2D::Physics::Rigidbody2D *rigidbody;
    Engine2D::ParticleSystem2D *particleSystem;

    void OnInitialize() override;
    void OnUpdate() override;

    void Reset();
};

#endif //BALL_H
