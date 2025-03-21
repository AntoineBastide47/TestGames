#ifndef Test_H
#define Test_H

#include <Engine2D/Game2D.hpp>

class Test : public Engine2D::Game2D {
  public:
    Test(int width, int height);

    void OnInitialize() override;
};


#endif //Test_H
