//
// Player.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include <Engine2D/ResourceManager.hpp>
#include <Engine/Input/Keyboard.hpp>

#include "Paddle.hpp"
#include "BrickBreaker.hpp"

void Paddle::OnInitialize() {
  Entity()->SetTexture(Engine2D::ResourceManager::GetTexture("paddle"));
  Transform()->SetScale({BrickBreaker::ViewportWidth() / 8, BrickBreaker::ViewportHeight() / 30});
  Transform()->SetPosition({0, (Transform()->GetScale().y - BrickBreaker::ViewportHeight()) * 0.5f});

  Entity()->AddComponent<Engine2D::Physics::BoxCollider2D>();

  Engine::Input::Keyboard::Q += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.held) {
      const float velocity = 50.0f * BrickBreaker::DeltaTime();
      if (const float bound = (Transform()->GetScale().x - BrickBreaker::ViewportWidth()) * 0.5f;
        Transform()->GetPosition().x >= bound)
        Transform()->SetPosition(
          {
            std::max(Transform()->GetPosition().x - velocity, bound), Transform()->GetPosition().y
          }
        );
    }
  };
  Engine::Input::Keyboard::D += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.held) {
      const float velocity = 50.0f * BrickBreaker::DeltaTime();
      if (const float bound = (BrickBreaker::ViewportWidth() - Transform()->GetScale().x) * 0.5f;
        Transform()->GetPosition().x <= bound)
        Transform()->SetPosition(
          {
            std::min(Transform()->GetPosition().x + velocity, bound), Transform()->GetPosition().y
          }
        );
    }
  };
}
