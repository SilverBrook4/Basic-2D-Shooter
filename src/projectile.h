#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "glm/glm.hpp"
#include "util/color.h"
#include "util/point.h"
#include "shapes/shape.h"
#include "shapes/rect.h"
#include "shapes/circle.h"
#include <memory>
#include <vector>

using glm::vec2, std::unique_ptr, std::shared_ptr, std::make_unique;

class Projectile {
protected:
  /// @breif the position vector of the projectile
  vec2 position;

  /// @breif the velocity (move speed) of the projectile
  float velocity;

  /// @breif the slope or direction to move the projectile in
  vec2 slope;

  /// @breif the direction the projectile is rotated in
  float direction;

  /// @breif the size the projectile is scaled to
  float scale;

  /// @breif constant the determines if hit boxes will be shown for projectiles
  /// @details true: shows hit boxes, false: hides hit boxes
  const bool SHOWHITBOX = false;

public:
  /// @brief creates a object of type projectile
  /// @param pos the position vector of the projectile
  /// @param velocity the velocity vector of the projectile
  /// @param shapes the vector of shapes comprising a projectile
  /// @param hitBox the vector of rects and points defining a hitbox
  /// @param scale the size the projectile is scaled too
  Projectile(Shader& shaderManager, vec2 pos, float velocity, vec2 slope, float scale);

  /// @breif a copy constructor for projectile
  /// @param other the projectile being coppied
  Projectile(Projectile const& other);

  /// @breif a deconstructor for projectile
  virtual ~Projectile() = default;

  /// @breif virtual move function
  virtual void move() = 0;

  /// @breif returns the position of projectile
  vec2 getPos();
  float getPosX();
  float getPosY();

  /// @breif sets the position of the projectile
  /// @param pos the position vector of the projectile
  /// @param x the x position of projectile
  /// @param y the y position of the projectile
  void setPos(vec2 pos);
  void setPosX(float x);
  void setPosY(float y);

  /// @breif returns the velocity of the projectile
  float getVelocity();

  /// @breif sets the velocity of projectile
  /// @param velocity the velocity vector of projectile
  /// @param x the x veclocity of projectile
  /// @param y the y velocity of projectile
  void setVelocity(float velocity);

  /// @breif sets the direction of the projectile
  /// @param theta the direction to shoot in
  /// @param deltaTime the time between frames
  void setDirection(float theta);

  /// @breif returns the direction of the projectile
  float getDirection();

  /// @breif sets scale of projectile
  /// @param s the scale of projectile
  void setScale(float s);
  float getScale();

  /// @breif returns the slope of the projectile as a vector, x, or y component
  vec2 getSlope();
  float getSlopeX();
  float getSlopeY();

  /// @breif virtual function that return the hit points of the projectile
  virtual vector<Point> getHitPoints() = 0;

  /// @breif virtual function that sets the uniforms and draws projectiles
  virtual void setUniformsAndDraw() = 0;
};

#endif //PROJECTILE_H
