//
// Ball.cpp
// Author: Antoine Bastide
// Date: 20/11/2024
//

#include <random>
#include <2D/ResourceManager.h>
#include <Input/Keyboard.h>

#include "Ball.h"
#include "BrickBreaker.h"

Engine2D::Vector2f Ball::INITIAL_VELOCITY = Engine2D::Vector2f{0, 10} * 100;

void Ball::Initialize() {
  SetTexture(Engine2D::ResourceManager::GetTexture("face"));
  transform.SetParent(BrickBreaker::Find<Paddle>("paddle"));
  transform.scale = Engine2D::Vector2f::One.Scaled({0.2f, 1}) * 1.5f;
  transform.position = Engine2D::Vector2f{0, 1.25f};

  AddComponent<Rigidbody2D>();
  rigidbody = GetComponent<Rigidbody2D>();
  rigidbody->SetType(Rigidbody2D::Circle, 1, Engine2D::Vector2f::Zero, transform.WorldHalfScale().x);
  rigidbody->isStatic = true;
  rigidbody->affectedByGravity = false;
  rigidbody->AddForce(INITIAL_VELOCITY);
  rigidbody->BindToViewport();

  Engine::Input::Keyboard::SPACE += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.pressed) {
      stuck = false;
      transform.SetParent(nullptr);
      this->rigidbody->isStatic = false;
    }
  };
}

void Ball::OnCollision(const std::shared_ptr<Rigidbody2D> &collider) {
  rigidbody->AddForce(INITIAL_VELOCITY * 0.1f);
}

void Ball::Reset() {
  this->transform.position = Engine2D::Vector2f::One.Scaled({0.2f, 1}) * 1.5f;
  transform.SetParent(BrickBreaker::paddle);
  stuck = true;
}
