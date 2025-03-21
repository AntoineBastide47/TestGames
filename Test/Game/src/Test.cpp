#include <Engine/Input/Keyboard.hpp>

#include "Test.hpp"

Test::Test(const int width, const int height) : Game2D(width, height, "Test") {}

void Test::OnInitialize() {
  Engine::Input::Keyboard::ESCAPE += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    Close(ctx);
  };
}