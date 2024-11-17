//
// Player.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include <Input/Keyboard.h>

#include "Player.h"

#include "BrickBreaker.h"

void Player::MoveLeft(const Engine::Input::KeyboardContext context) {
  if (context.held) {
    const float velocity = 500.0f * BrickBreaker::DeltaTime();
    this->transform.position.x = std::max(this->transform.position.x - velocity, 0.0f);
  }
}

void Player::MoveRight(const Engine::Input::KeyboardContext context) {
  if (context.held) {
    const float velocity = 500.0f * BrickBreaker::DeltaTime();
    this->transform.position.x = std::min(
                                          this->transform.position.x + velocity,
                                          static_cast<float>(BrickBreaker::Width()) - this->transform.scale.x
                                         );
  }
}

void Player::Initialize() {
  transform.scale = Engine2D::Vector2{100, 20};
  transform.position = Engine2D::Vector2{
    static_cast<float>(BrickBreaker::Width()) / 2.0f - transform.scale.x / 2.0f,
    static_cast<float>(BrickBreaker::Height()) - transform.scale.y
  };

  Engine::Input::Keyboard::A += [this](const Engine::Input::KeyboardContext ctx) {
    MoveLeft(ctx);
  };
  Engine::Input::Keyboard::D += [this](const Engine::Input::KeyboardContext ctx) {
    MoveRight(ctx);
  };
}
