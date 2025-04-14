#ifndef BULLET_H
#define BULLET_H

#include "projectile.h"

class Bullet : public Projectile {
private:
  /// @breif const size for the bullet to help with correct scaling
  const float SIZE = 15.0f;

  /// @breif a vector of shape that make up the bullet
  vector<shared_ptr<Shape>> shapes;

  /// @breif a vector of boxes that make up the bullets hit boxes
  vector<shared_ptr<Rect>> hitBox;

  /// @breif a vector of Points that make up the bullets hit points for collision
  vector<Point> hitPoints;

public:
  /// @breif constructor for the Bullet class
  /// @param shader the shader to render the bullet
  /// @param pos the start position of the bullet
  /// @param velocity the velocity or speed of the bullet
  /// @param slope the slope vector of the bullet
  /// @param scale the scale of the bullet from its base size
  /// @param deltaTime the time between frames when bullet is spawned
  Bullet(Shader& shader, vec2 pos, float velocity, vec2 slope, float scale, float deltaTime);

  /// @breif a copy constructor for buller
  /// @param other the bullet being copied
  Bullet(Bullet const& other);

  /// @breif bullet deconstructor
  ~Bullet() override;

  /// @breif moves the bullet velocity units in the direction of the slope
  void move() override;

  /// @breif sets the uniforms of the bullet and draws it
  void setUniformsAndDraw() override;

  /// @breif returns the hitpoints of the bullet for collision checks
  vector<Point> getHitPoints() override;
};



#endif //BULLET_H
