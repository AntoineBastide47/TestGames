//
// Player.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef PADDLE_H
#define PADDLE_H

#include <Engine2D/Behaviour.hpp>
#include "Paddle.gen.hpp"

class Paddle final : public Engine2D::Behaviour {
  SERIALIZE_PADDLE
  public:
    void OnInitialize() override;
    void OnBindInput() override;
};

#endif //PADDLE_H
