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
#include <glm/glm.hpp>
#include <Engine2D/Physics/Collider2D.hpp>
#include <Engine2D/Rendering/Camera2D.hpp>

#include "Ball.hpp"
#include "BrickBreaker.hpp"

glm::vec2 Ball::INITIAL_VELOCITY = glm::vec2(0, 10) * 100.0f;

Ball::Ball() : rigidbody(nullptr), particleSystem(nullptr) {}

void Ball::OnInitialize() {
  Transform()->SetParent(BrickBreaker::Find("paddle"));
  Transform()->SetPositionRotationAndScale(glm::vec2(0, 1.35f), 0, glm::vec2(0.3f, 1.5f) * 1.1f);

  // Set up the renderer
  const auto renderer = Entity()->AddComponent<Engine2D::Rendering::SpriteRenderer>();
  renderer->SetSprite(Engine::ResourceManager::GetSprite("face"));
  renderer->SetRenderOrder(2);

  // Set up the shake coefficients for the camera
  const auto cam = Engine2D::Game2D::MainCamera();
  cam->shakeCoefficientsX = {{4.125f, 15.6f, 1.725f}, {1.65f, 4.2f, 3.75f}, {1.35f, 8.4f, 0.75f}};
  cam->shakeCoefficientsY = {{3, 13.2f, -1.875f}, {2.1f, 7.2f, 3}, {1.2f, 1.2f, 0.0f}};

  // Set up the rigidbody
  Entity()->AddComponent<Engine2D::Physics::CircleCollider2D>();
  rigidbody = Entity()->AddComponent<Engine2D::Physics::Rigidbody2D>();
  rigidbody->isKinematic = true;
  rigidbody->angularDamping = 0.01f;

  // Set up the particle system
  particleSystem = Entity()->AddComponent<Engine2D::ParticleSystem2D>();
  particleSystem->SetSprite(Engine::ResourceManager::GetSprite("particle"));
  particleSystem->SetMaxParticles(100);
  particleSystem->loop = true;
  particleSystem->SetDuration(1);
  particleSystem->SetParticleLifetime(1);
  particleSystem->SetRenderOrder(1);
  particleSystem->startColor = glm::vec4(1, 1, 0, 1);
  particleSystem->endColor = glm::vec4(0, 0, 1, 1);
  particleSystem->startScale = glm::vec2(2);
  particleSystem->startAngularVelocity = 360;
  particleSystem->endAngularVelocity = -360;

  Engine::Input::Keyboard::SPACE += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.pressed && stuck) {
      stuck = false;
      Transform()->SetParent(nullptr);
      rigidbody->isKinematic = false;
      rigidbody->affectedByGravity = false;
      rigidbody->AddForce(INITIAL_VELOCITY);
      particleSystem->SetDuration(2);
    }
  };
}

void Ball::OnUpdate() {
  // Get half-dimensions of the screen
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

  particleSystem->startVelocity = -rigidbody->linearVelocity * 0.25f;
  particleSystem->endVelocity = rigidbody->linearVelocity * 0.25f;
}

void Ball::Reset() {
  Transform()->SetPositionRotationAndScale(glm::vec2(0.2f, 1) * 1.5f, 0, Transform()->GetScale());
  stuck = true;
}
