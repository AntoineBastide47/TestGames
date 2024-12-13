//
// Player.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include <Input/Keyboard.h>

#include "Paddle.h"

#include <iostream>

#include "BrickBreaker.h"

Paddle::Paddle(const std::string &name, Entity2D *parent, Texture2D *texture) : Entity2D(name, parent, texture) {}

void Paddle::Initialize() {
  transform.scale = Engine2D::Vector2{10, 2};
  transform.position = Engine2D::Vector2{0, (transform.scale->y - BrickBreaker::ViewportHeight()) * 0.5f};
  rigidbody = Engine2D::Physics::Rigidbody2D::CreateRectangleBody(transform.scale->x, transform.scale->y, 100, 1, true);
  AddComponent(rigidbody);

  Engine::Input::Keyboard::Q += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.held) {
      const float velocity = 50.0f * BrickBreaker::DeltaTime();
      if (const float bound = (transform.scale->x - BrickBreaker::ViewportWidth()) * 0.5f; transform.position->x >= bound)
        this->transform.position->x = std::max(this->transform.position->x - velocity, bound);
    }
  };
  Engine::Input::Keyboard::D += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.held) {
      const float velocity = 50.0f * BrickBreaker::DeltaTime();
      if (const float bound = (BrickBreaker::ViewportWidth() - transform.scale->x) * 0.5f; transform.position->x <= bound)
        this->transform.position->x = std::min(this->transform.position->x + velocity, bound);
    }
  };
}
