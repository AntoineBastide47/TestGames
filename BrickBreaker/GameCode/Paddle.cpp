//
// Player.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include <2D/ResourceManager.h>
#include <2D/Physics/Rigidbody2D.h>
#include <Input/Keyboard.h>

#include "Paddle.h"
#include "BrickBreaker.h"

void Paddle::OnInitialize() {
  SetTexture(Engine2D::ResourceManager::GetTexture("paddle"));
  transform.scale = Engine2D::Vector2f{BrickBreaker::ViewportWidth() / 8, BrickBreaker::ViewportHeight() / 30};
  transform.position = Engine2D::Vector2f{0, (transform.scale->y - BrickBreaker::ViewportHeight()) * 0.5f};

  AddComponent<Engine2D::Physics::RectangleCollider2D>();
  AddComponent<Engine2D::Physics::Rigidbody2D>()->isKinematic = true;

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
