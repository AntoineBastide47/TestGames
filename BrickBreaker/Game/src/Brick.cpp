//
// Brick.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include <Engine2D/Rendering/SpriteRenderer.hpp>
#include <Engine2D/Physics/Collider2D.hpp>
#include <Engine2D/Rendering/Camera2D.hpp>

#include "Brick.hpp"
#include "BrickBreaker.hpp"

void Brick::OnInitialize() {
  Entity()->AddComponent<Engine2D::Physics::BoxCollider2D>();
}

void Brick::OnCollisionEnter2D(const std::shared_ptr<Engine2D::Physics::Collider2D> &) {
  Engine2D::Game2D::MainCamera()->Shake(0.5f);
  if (!isSolid) {
    lives -= 1;
    if (lives <= 0)
      Entity()->Destroy();
    Entity()->GetComponent<Engine2D::Rendering::SpriteRenderer>()->SetColor(GetColor(isSolid, lives));
  }
}

glm::vec4 Brick::GetColor(const bool isSolid, const int lives) {
  switch (isSolid ? lives : lives + 1) {
    case 1: return glm::vec4(0.8f, 0.8f, 0.7f, 1.0f);
    case 2: return glm::vec4(0.2f, 0.6f, 1.0f, 1.0f);
    case 3: return glm::vec4(0.0f, 0.7f, 0.0f, 1.0f);
    case 4: return glm::vec4(0.8f, 0.8f, 0.4f, 1.0f);
    case 5: return glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);
    default: return glm::vec4(0, 0, 0, 1);
  }
}
