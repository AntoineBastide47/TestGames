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
    bool stuck = true;

    Ball();

    Engine2D::Physics::Rigidbody2D *rigidbody;
    Engine2D::ParticleSystem2D *particleSystem;

    void OnInitialize() override;
    void OnBindInput() override;
    void OnUpdate() override;
    void OnDeserialize(Engine::Reflection::Format format, const Engine::JSON &json) override;

    void Reset();
};

#endif //BALL_H
