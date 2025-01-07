//
// Brick.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef BRICK_H
#define BRICK_H

#include <2D/Entity2D.h>

class Brick final : public Engine2D::Entity2D {
  public:
    int lives;
    bool isSolid;

    explicit Brick(const std::string &name) : Entity2D(name), lives(0), isSolid(false) {}

    void OnInitialize() override;
    void OnCollisionEnter2D(const std::shared_ptr<Engine2D::Physics::Collider2D> &collider) override;
  private:
    static glm::vec3 GetColor(bool isSolid, int lives);
};

#endif //BRICK_H
