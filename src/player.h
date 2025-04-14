#ifndef PLAYER_H
#define PLAYER_H

#include "glm/glm.hpp"
#include "util/color.h"
#include "shapes/circle.h"
#include "shapes/gun.h"
#include <memory>

using glm::vec2, std::unique_ptr, std::make_unique;

class Player {
private:
  /// @breif the rectangle that makes up the gun portion of player
  unique_ptr<Gun> gun;

  /// @breif the circle that makes up the body of the player
  unique_ptr<Circle> body;

  /// @breif the position vector of the player
  vec2 pos;

  /// @breif the angle the player is aimed at
  float angle;

  /// @breif the speed the player moves at
  float speed;

public:
  /// @brief Constructs a new Player object
  /// @param pos the position of the player
  /// @param scale the size of the player
  /// @param color the color of the player
  Player(Shader& shader,vec2 pos, float scale, struct color color);

  /// @breif sets the uniforms and draws player
  void setUniformsAndDraw();

  /// @breif sets the angle of rotation of player
  /// @param theta the angle being set too
  /// @param deltaTime the time between frames
  void setRotation(float theta, float deltaTime);

  /// @breif moves player in direction by increment
  /// @param x offset of x movement
  /// @param y offset of y movment
  /// @param offset the amount moved in x and y direction
  void moveX(float x);
  void moveY(float y);
  void move(vec2 offset);

  /// @breif sets the speed of the player
  /// @params speed how fast the player moves
  void setSpeed(float speed);

  /// @breif return the player speed
  /// @return speed how fast the charater moves
  float getSpeed();

  /// @breif sets the position of the player
  /// @param posX the x position of the player
  /// @param posY the y position of the player
  /// @param pos the position vector of the player
  void setPosX(float posX);
  void setPosY(float posY);
  void setPos(vec2 pos);

  /// @breif returns the position of the player
  float getPosX();
  float getPosY();
  vec2 getPos();

  /// @breif returns size of the player
  float getRadius();

  /// @breif getters for edges of player
  float getLeft();
  float getRight();
  float getTop();
  float getBottom();
};



#endif //PLAYER_H
