//
// Brick.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef BRICK_H
#define BRICK_H

#include <2D/Entity2D.h>
#include <2D/Physics/Rigidbody2D.h>

class Brick final : public Engine2D::Entity2D {
  public:
    int lives;
    bool isSolid;
    Engine2D::Physics::Rigidbody2D *rigidbody;

    Brick(const std::string &name, Entity2D *parent, Texture2D *texture, bool isSolid, int lives);

    void Initialize() override;
    void OnCollision(Engine2D::Physics::Rigidbody2D *rigidbody) override;
  private:
    static glm::vec3 GetColor(bool isSolid, int lives);
};

#endif //BRICK_H
