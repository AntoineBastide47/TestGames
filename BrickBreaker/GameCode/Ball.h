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
    bool stuck;
    static Engine2D::Vector2 INITIAL_VELOCITY;
    Engine2D::Physics::Rigidbody2D *rigidbody;

    Ball(const std::string &name, Texture2D *sprite);

    void Initialize() override;
    void OnCollision(Engine2D::Physics::Rigidbody2D *collider) override;

    void Reset();
};

#endif //BALL_H
