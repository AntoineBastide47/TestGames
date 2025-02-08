//
// Player.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include <Engine2D/ResourceManager.h>
#include <Input/Keyboard.h>

#include "Paddle.h"
#include "BrickBreaker.h"

void Paddle::OnInitialize() {
  SetTexture(Engine2D::ResourceManager::GetTexture("paddle"));
  transform.SetScale({BrickBreaker::ViewportWidth() / 8, BrickBreaker::ViewportHeight() / 30});
  transform.SetPosition({0, (transform.GetScale().y - BrickBreaker::ViewportHeight()) * 0.5f});

  AddComponent<Engine2D::Physics::RectangleCollider2D>();

  Engine::Input::Keyboard::Q += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.held) {
      const float velocity = 50.0f * BrickBreaker::DeltaTime();
      if (const float bound = (transform.GetScale().x - BrickBreaker::ViewportWidth()) * 0.5f;
        transform.GetPosition().x >= bound)
        this->transform.SetPosition({std::max(transform.GetPosition().x - velocity, bound), transform.GetPosition().y});
    }
  };
  Engine::Input::Keyboard::D += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.held) {
      const float velocity = 50.0f * BrickBreaker::DeltaTime();
      if (const float bound = (BrickBreaker::ViewportWidth() - transform.GetScale().x) * 0.5f;
        transform.GetPosition().x <= bound)
        this->transform.SetPosition({std::min(transform.GetPosition().x + velocity, bound), transform.GetPosition().y});
    }
  };
}