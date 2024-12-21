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
    std::shared_ptr<Engine2D::Physics::Rigidbody2D> rigidbody;

    explicit Brick(const std::string &name) : Entity2D(name), lives(0), isSolid(false), rigidbody(nullptr) {}

    void Initialize() override;
    void OnCollision(const std::shared_ptr<Engine2D::Physics::Rigidbody2D> &collider) override;
  private:
    static glm::vec3 GetColor(bool isSolid, int lives);
};

#endif //BRICK_H
