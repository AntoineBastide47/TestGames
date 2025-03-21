//
// Ball.h
// Author: Antoine Bastide
// Date: 20/11/2024
//

#ifndef BALL_H
#define BALL_H

#include <Engine2D/Behaviour.hpp>
#include <Engine2D/Physics/Rigidbody2D.hpp>

namespace Engine2D {
  class ParticleSystem2D;
}

class Ball : public Engine2D::Behaviour {
  public:
    static glm::vec2 INITIAL_VELOCITY;

    Ball();

    bool stuck = true;
    std::shared_ptr<Engine2D::Physics::Rigidbody2D> rigidbody;
    std::shared_ptr<Engine2D::ParticleSystem2D> particleSystem;

    void OnInitialize() override;
    void OnUpdate() override;

    void Reset();
};

#endif //BALL_H
