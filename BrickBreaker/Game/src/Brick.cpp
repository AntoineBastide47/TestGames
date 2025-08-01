//
// Brick.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include <Engine2D/Physics/Collider2D.hpp>
#include <Engine2D/Rendering/Camera2D.hpp>
#include <Engine2D/SceneManagement/SceneManager.hpp>

#include "Brick.hpp"
#include "BrickBreaker.hpp"

void Brick::OnInitialize() {
  Entity()->AddComponent<Engine2D::Physics::BoxCollider2D>();
}

void Brick::OnCollisionEnter2D(const Engine2D::Physics::Collider2D *) {
  Engine2D::SceneManager::ActiveScene()->MainCamera()->Shake(0.5f);
  if (!isSolid)
    Entity()->Destroy();
}

glm::vec4 Brick::GetColor(const bool isSolid, const int lives) {
  switch (isSolid ? lives : lives + 1) {
    case 1:
      return {0.8f, 0.8f, 0.7f, 1.0f};
    case 2:
      return {0.2f, 0.6f, 1.0f, 1.0f};
    case 3:
      return {0.0f, 0.7f, 0.0f, 1.0f};
    case 4:
      return {0.8f, 0.8f, 0.4f, 1.0f};
    case 5:
      return {1.0f, 0.5f, 0.0f, 1.0f};
    default:
      return {0, 0, 0, 1};
  }
}
