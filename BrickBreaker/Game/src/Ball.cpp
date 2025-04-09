//
// Ball.cpp
// Author: Antoine Bastide
// Date: 20/11/2024
//

#include <Engine/ResourceManager.hpp>
#include <Engine/Input/Keyboard.hpp>
#include <Engine2D/ParticleSystem/ParticleSystem2D.hpp>
#include <Engine/Settings.hpp>
#include <Engine2D/Rendering/SpriteRenderer.hpp>

#include "Ball.hpp"
#include "BrickBreaker.hpp"

glm::vec2 Ball::INITIAL_VELOCITY = glm::vec2(3, 10) * 100.0f;

Ball::Ball() : rigidbody(nullptr), particleSystem(nullptr) {}

void Ball::OnInitialize() {
  Entity()->AddComponent<Engine2D::Rendering::SpriteRenderer>()->sprite = Engine::ResourceManager::GetSprite("face");
  Transform()->SetParent(BrickBreaker::Find("paddle"));
  Transform()->SetPositionRotationAndScale(glm::vec2(0, 1.25f), 0, glm::vec2(0.3f, 1.5f));

  Entity()->AddComponent<Engine2D::Physics::CircleCollider2D>();
  rigidbody = Entity()->AddComponent<Engine2D::Physics::Rigidbody2D>();
  rigidbody->isKinematic = true;

  particleSystem = Entity()->AddComponent<Engine2D::ParticleSystem2D>();
  particleSystem->texture = Engine::ResourceManager::GetTexture("particle");
  particleSystem->SetMaxParticles(100);
  particleSystem->loop = true;
  particleSystem->SetDuration(0);
  particleSystem->particleLifetime = 2;

  particleSystem->startColor = glm::vec4(1, 1, 0, 1);
  particleSystem->endColor = glm::vec4(1, 1, 1, 1);
  particleSystem->startSize = glm::vec2(1.5f);

  particleSystem->startAngularVelocity = 360;
  particleSystem->endAngularVelocity = -360;

  Engine::Input::Keyboard::SPACE += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.pressed && stuck) {
      stuck = false;
      Transform()->SetParent(nullptr);
      rigidbody->isKinematic = false;
      rigidbody->affectedByGravity = false;
      rigidbody->AddForce(INITIAL_VELOCITY);
      particleSystem->SetDuration(1);
    }
  };
}

void Ball::OnUpdate() {
  // Get half dimensions of the screen
  const float halfWidth = BrickBreaker::ViewportWidth() * 0.5f;
  const float halfHeight = BrickBreaker::ViewportHeight() * 0.5f;
  const auto transform = Transform();

  // Check for collisions with the left and right boundaries
  if (transform->GetPosition().x <= -halfWidth + transform->GetScale().x * 0.5f) {
    rigidbody->linearVelocity.x = -rigidbody->linearVelocity.x;
    transform->SetPosition({-halfWidth + transform->GetScale().x * 0.5f, transform->GetPosition().y});
  } else if (transform->GetPosition().x >= halfWidth - transform->GetScale().x * 0.5f) {
    rigidbody->linearVelocity.x = -rigidbody->linearVelocity.x;
    transform->SetPosition({halfWidth - transform->GetScale().x * 0.5f, transform->GetPosition().y});
  }

  // Check for collisions with the top and bottom boundaries
  if (transform->GetPosition().y <= -halfHeight + transform->GetScale().y * 0.5f) {
    rigidbody->linearVelocity.y = -rigidbody->linearVelocity.y;
    transform->SetPosition({transform->GetPosition().x, -halfHeight + transform->GetScale().y * 0.5f});
  } else if (transform->GetPosition().y >= halfHeight - transform->GetScale().y * 0.5f) {
    rigidbody->linearVelocity.y = -rigidbody->linearVelocity.y;
    transform->SetPosition({transform->GetPosition().x, halfHeight - transform->GetScale().y * 0.5f});
  }

  particleSystem->startVelocity = -rigidbody->linearVelocity;
  particleSystem->endVelocity = rigidbody->linearVelocity;
}

void Ball::Reset() {
  Transform()->SetPositionRotationAndScale(glm::vec2(0.2f, 1) * 1.5f, 0, Transform()->GetScale());
  stuck = true;
}
