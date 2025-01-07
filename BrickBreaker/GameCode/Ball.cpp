//
// Ball.cpp
// Author: Antoine Bastide
// Date: 20/11/2024
//

#include <2D/ResourceManager.h>
#include <Input/Keyboard.h>

#include "Ball.h"
#include "BrickBreaker.h"

Engine2D::Vector2f Ball::INITIAL_VELOCITY = Engine2D::Vector2f{0, 10} * 100;

void Ball::OnInitialize() {
  SetTexture(Engine2D::ResourceManager::GetTexture("face"));
  transform.SetParent(BrickBreaker::Find<Paddle>("paddle"));
  transform.scale = Engine2D::Vector2f{0.3f, 1.5f};
  transform.position = Engine2D::Vector2f{0, 1.25f};

  AddComponent<Engine2D::Physics::CircleCollider2D>();
  rigidbody = AddComponent<Engine2D::Physics::Rigidbody2D>();
  rigidbody->isKinematic = true;
  rigidbody->affectedByGravity = false;

  Engine::Input::Keyboard::SPACE += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.pressed && stuck) {
      stuck = false;
      transform.SetParent(nullptr);
      rigidbody->isKinematic = false;
      rigidbody->AddForce(INITIAL_VELOCITY);
    }
  };
}

void Ball::OnUpdate() {
  // Get half dimensions of the screen
  const float halfWidth = BrickBreaker::ViewportWidth() * 0.5f;
  const float halfHeight = BrickBreaker::ViewportHeight() * 0.5f;

  // Check for collisions with the left and right boundaries
  if (transform.position->x <= -halfWidth + transform.scale->x * 0.5f) {
    rigidbody->linearVelocity.x = -rigidbody->linearVelocity.x;
    transform.position->x = -halfWidth + transform.scale->x * 0.5f;
  }
  else if (transform.position->x >= halfWidth - transform.scale->x * 0.5f) {
    rigidbody->linearVelocity.x = -rigidbody->linearVelocity.x;
    transform.position->x = halfWidth - transform.scale->x * 0.5f;
  }

  // Check for collisions with the top and bottom boundaries
  if (transform.position->y <= -halfHeight + transform.scale->y * 0.5f) {
    rigidbody->linearVelocity.y = -rigidbody->linearVelocity.y;
    transform.position->y = -halfHeight + transform.scale->y * 0.5f;
  }
  else if (transform.position->y >= halfHeight - transform.scale->y * 0.5f) {
    rigidbody->linearVelocity.y = -rigidbody->linearVelocity.y;
    transform.position->y = halfHeight - transform.scale->y * 0.5f;
  }
}

void Ball::Reset() {
  this->transform.position = Engine2D::Vector2f::One.Scaled({0.2f, 1}) * 1.5f;
  transform.SetParent(BrickBreaker::paddle);
  stuck = true;
}
