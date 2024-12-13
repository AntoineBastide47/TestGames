//
// Brick.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include <2D/Physics/Rigidbody2D.h>

#include "Brick.h"

Brick::Brick(const std::string &name, Entity2D *parent, Texture2D *texture, const bool isSolid, const int lives)
  : Entity2D(name, parent, texture), lives(lives), isSolid(isSolid) {
  textureColor = GetColor(isSolid, lives);
}

void Brick::Initialize() {
  rigidbody = Engine2D::Physics::Rigidbody2D::CreateRectangleBody(transform.scale->x, transform.scale->y, 100, 1, true);
  rigidbody->affectedByGravity = false;
  AddComponent(rigidbody);
}

void Brick::OnCollision(Engine2D::Physics::Rigidbody2D *rigidbody) {
  if (rigidbody->Type() == Engine2D::Physics::Rigidbody2D::Circle && !isSolid) {
    lives -= 1;
    textureColor = GetColor(isSolid, lives);
    if (lives <= 0)

      Destroy();
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
