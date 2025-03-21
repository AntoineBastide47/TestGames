//
// Player.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef PADDLE_H
#define PADDLE_H

#include <Engine2D/Behaviour.hpp>

class Paddle : public Engine2D::Behaviour {
  public:
    void OnInitialize() override;
};

#endif //PADDLE_H
