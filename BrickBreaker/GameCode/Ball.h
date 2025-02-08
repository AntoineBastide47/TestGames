//
// Ball.h
// Author: Antoine Bastide
// Date: 20/11/2024
//

#ifndef BALL_H
#define BALL_H

#include <Engine2D/Entity2D.h>
#include <Engine2D/Physics/Rigidbody2D.h>

class Ball : public Engine2D::Entity2D {
  public:
    static glm::vec2 INITIAL_VELOCITY;

    bool stuck = true;
    std::shared_ptr<Engine2D::Physics::Rigidbody2D> rigidbody;
    std::shared_ptr<Engine2D::ParticleSystem2D> particleSystem;

    explicit Ball(const std::string &name) : Entity2D(name) {}

    void OnInitialize() override;
    void OnUpdate() override;

    void Reset();
};

#endif //BALL_H
