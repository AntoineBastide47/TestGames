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
    Brick(
      const std::string &name, Entity2D *parent, Engine2D::Rendering::Texture2D *texture, const bool isSolid
    )
      : Entity2D(name, parent, texture),
        isSolid(isSolid),
        destroyed(false) {}

    bool isSolid;
    bool destroyed;
};

#endif //BRICK_H
