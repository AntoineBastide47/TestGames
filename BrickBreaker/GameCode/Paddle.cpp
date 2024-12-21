//
// Player.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include <2D/ResourceManager.h>
#include <Input/Keyboard.h>

#include "Paddle.h"
#include "BrickBreaker.h"

void Paddle::Initialize() {
  SetTexture(Engine2D::ResourceManager::GetTexture("paddle"));
  transform.scale = Engine2D::Vector2f{10, 2};
  transform.position = Engine2D::Vector2f{0, (transform.scale->y - BrickBreaker::ViewportHeight()) * 0.5f};

  AddComponent<Rigidbody2D>();
  rigidbody = GetComponent<Rigidbody2D>();
  rigidbody->SetType(Rigidbody2D::Rectangle, 100, transform.WorldPosition(), 0);
  rigidbody->BindToViewport();
  rigidbody->isStatic = true;

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
