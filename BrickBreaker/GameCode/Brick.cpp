//
// Brick.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include "Brick.h"
#include "BrickBreaker.h"

void Brick::OnInitialize() {
  textureColor = GetColor(isSolid, lives);
  AddComponent<Engine2D::Physics::RectangleCollider2D>();
}

void Brick::OnCollisionEnter2D(const std::shared_ptr<Engine2D::Physics::Collider2D> &collider) {
  if (!isSolid){
    lives -= 1;
    if (lives <= 0)
      Destroy();
    textureColor = GetColor(isSolid, lives);
  }
}

glm::vec3 Brick::GetColor(const bool isSolid, const int lives) {
  switch (isSolid ? lives : lives + 1) {
    case 1: return glm::vec3(0.8f, 0.8f, 0.7f);
    case 2: return glm::vec3(0.2f, 0.6f, 1.0f);
    case 3: return glm::vec3(0.0f, 0.7f, 0.0f);
    case 4: return glm::vec3(0.8f, 0.8f, 0.4f);
    case 5: return glm::vec3(1.0f, 0.5f, 0.0f);
    default: return glm::vec3(0.0f);
  }
}
