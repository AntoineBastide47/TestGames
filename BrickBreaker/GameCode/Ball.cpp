//
// Ball.cpp
// Author: Antoine Bastide
// Date: 20/11/2024
//

#include <random>
#include <Input/Keyboard.h>

#include "Ball.h"
#include "BrickBreaker.h"

Engine2D::Vector2 Ball::INITIAL_VELOCITY = Engine2D::Vector2{1, 10} * 100;

Ball::Ball(const std::string &name, Texture2D *sprite)
  : Entity2D(name, nullptr, sprite), stuck(true) {}

void Ball::Initialize() {
  transform.SetParent(BrickBreaker::paddle);
  transform.scale = Engine2D::Vector2::One.Scaled({0.2f, 1}) * 1.5f;
  transform.position = Engine2D::Vector2{0, 1.25f};

  rigidbody = Engine2D::Physics::Rigidbody2D::CreateCircleBody(transform.scale->x * 0.5f, 1, 1, true);
  rigidbody->affectedByGravity = false;
  rigidbody->AddForce(INITIAL_VELOCITY);
  rigidbody->BindToViewport();
  AddComponent(rigidbody);

  Engine::Input::Keyboard::SPACE += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.pressed) {
      stuck = false;
      transform.SetParent(nullptr);
      this->rigidbody->isStatic = false;
    }
  };
}

void Ball::OnCollision(Engine2D::Physics::Rigidbody2D *collider) {
  rigidbody->AddForce(INITIAL_VELOCITY * 0.1f);
}

void Ball::Reset() {
  this->transform.position = Engine2D::Vector2::One.Scaled({0.2f, 1}) * 1.5f;
  transform.SetParent(BrickBreaker::paddle);
  stuck = true;
}
