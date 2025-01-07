//
// Ball.h
// Author: Antoine Bastide
// Date: 20/11/2024
//

#ifndef BALL_H
#define BALL_H

#include <2D/Entity2D.h>
#include <2D/Physics/Rigidbody2D.h>

class Ball : public Engine2D::Entity2D {
  public:
    bool stuck = true;
    static Engine2D::Vector2f INITIAL_VELOCITY;
    std::shared_ptr<Engine2D::Physics::Rigidbody2D> rigidbody;

    explicit Ball(const std::string &name) : Entity2D(name) {}

    void OnInitialize() override;
    void OnUpdate() override;

    void Reset();
};

#endif //BALL_H
