//
// SpaceInvaders.cpp
// Author: Antoine Bastide
// Date: 02/11/2024
//

#include "2D/ResourceManager.h"
#include "2D/Rendering/SpriteRenderer.h"
#include "BrickBreaker.h"

using Engine2D::ResourceManager;
using Engine2D::Rendering::SpriteRenderer;

BrickBreaker::BrickBreaker(const int16 width, const int16 height)
: Game2D(width, height, "Space Invaders"), levelIndex(0),
  background(nullptr), player(nullptr) {}

void BrickBreaker::Initialize() {
  // load textures
  ResourceManager::LoadTexture("Assets/Textures/background.jpg", false, "background");
  ResourceManager::LoadTexture("Assets/Textures/block.png", false, "block");
  ResourceManager::LoadTexture("Assets/Textures/block_solid.png", false, "block_solid");
  ResourceManager::LoadTexture("Assets/Textures/paddle.png", true, "paddle");

  this->background = new Engine2D::Entity2D("background", nullptr, ResourceManager::GetTexture("background"));
  background->transform.scale = Engine2D::Vector2(this->width, this->height);
  this->player = new Player("player", nullptr, ResourceManager::GetTexture("paddle"));

  // Load the game levels
  this->levels.emplace_back(0, this->width, this->height / 2);
  this->levels.emplace_back(1, this->width, this->height / 2);
  this->levels.emplace_back(2, this->width, this->height / 2);
  this->levels.emplace_back(3, this->width, this->height / 2);

  // Load level 0 and unload all the others
  ChangeLevel(0);
}

void BrickBreaker::ChangeLevel(const int newLevel) {
  for (int i = 0; i < this->levels.size(); ++i)
    for (const auto brick : this->levels[i].bricks)
      brick->SetActive(i == newLevel);
  this->levelIndex = newLevel;
}