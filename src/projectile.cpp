#include "projectile.h"

Projectile::Projectile(Shader &shader, vec2 pos, float velocity, vec2 slopeI, float scale) : position(pos),  velocity(velocity), scale(scale) {
    // sets direction in degrees
    direction = atan2(slopeI.y, slopeI.x) * (180/M_PI);

    // normalize slope triangle
    float hypotenuse = sqrt(pow(slopeI.x, 2) + pow(slopeI.y, 2));
    slope = vec2(slopeI.x / hypotenuse, slopeI.y /hypotenuse);
}

Projectile::Projectile(Projectile const &other) : position(other.position), velocity(other.velocity), slope(other.slope), direction(other.direction), scale(other.scale) {
}

// position setters and getters
void Projectile::setPos(vec2 pos) {position = pos;}
void Projectile::setPosX(float x) {position.x = x;}
void Projectile::setPosY(float y) {position.y = y;}

vec2 Projectile::getPos()   {return position;}
float Projectile::getPosX() {return position.x;}
float Projectile::getPosY() {return position.y;}

// velocity setters and getters
void Projectile::setVelocity(float v)    {velocity = v;}

float Projectile::getVelocity()      {return velocity;}

// direction setter and getter
void Projectile::setDirection(float theta) {direction = theta;}
float Projectile::getDirection() {return direction;}


// scale setter and getter
void Projectile::setScale(float s)  {scale = s;}
float Projectile::getScale()        {return scale;}

// slope getter
vec2 Projectile::getSlope() {return slope;}
float Projectile::getSlopeX() {return slope.x;}
float Projectile::getSlopeY() {return slope.y;}







