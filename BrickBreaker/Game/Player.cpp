//
// Player.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include "Player.h"

#include "BrickBreaker.h"

void Player::Initialize() {
  transform.scale = Engine2D::Vector2{100, 20};
  transform.position = Engine2D::Vector2{
    static_cast<float>(BrickBreaker::Instance()->Width()) / 2.0f - transform.scale.x / 2.0f,
    static_cast<float>(BrickBreaker::Instance()->Height()) - transform.scale.y
  };
}

void Player::ProcessInput() {
  const float velocity = 500.0f * BrickBreaker::Instance()->DeltaTime();
  if (BrickBreaker::Instance()->keys[GLFW_KEY_A])
    transform.position.x = std::max(transform.position.x - velocity, 0.0f);
  if (BrickBreaker::Instance()->keys[GLFW_KEY_D])
    transform.position.x = std::min(
                                    transform.position.x + velocity,
                                    static_cast<float>(BrickBreaker::Instance()->Width()) - transform.scale.x
                                   );
}
