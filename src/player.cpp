#include "player.h"

Player::Player(Shader &shader, vec2 pos, float scale, ::color color) {
    // initilizes its body and gun
    body = make_unique<Circle>(shader, pos, scale, vec2(), color);
    gun = make_unique<Gun>(shader, pos, vec2(2 * scale, 1 * scale), color);
    // initilizes its angle and speed
    angle = 0.0f;
    speed = 2.5f;
}

void Player::setUniformsAndDraw() {
    if (gun) { // sets uniforms of gun compenent, draws it, and check for initilization
        gun->setUniforms();
        gun->draw();
    } else {
        cout << "ERROR: gun not initilaized" << endl;
    }
    if (body) { // sets uniforms of body compenent, draws it, and check for initilization
        body->setUniforms();
        body->draw();
    } else {
        cout << "ERROR: body not initialized" << endl;
    }
}

void Player::setRotation(float theta, float deltaTime) {
    // rotates gun in direction of mouse
    gun->setRotation(theta, deltaTime);
}

// movement
void Player::moveX(float x)     {body->moveX(x); gun->moveX(x);}
void Player::moveY(float y)     {body->moveY(y); gun->moveY(y);}
void Player::move(vec2 offset)  {body->move(offset); gun->move(offset);}

// speed getter and setter
void Player::setSpeed(float speedI) {speed = speedI;}
float Player::getSpeed()            {return speed;}


// position setters
void Player::setPosX(float posX)    {body->setPosX(posX); gun->setPosX(posX); pos.x = posX;}
void Player::setPosY(float posY)    {body->setPosY(posY); gun->setPosY(posY); pos.y = posY;}
void Player::setPos(vec2 posI)       {body->setPos(posI); gun->setPos(posI); pos = posI;}

// position getters
float Player::getPosX() {return body->getPosX();}
float Player::getPosY() {return body->getPosY();}
vec2 Player::getPos()   {return body->getPos();}

// size getters and setters
float Player::getRadius() {return body->getRadius();}

float Player::getTop() {return body->getTop();}
float Player::getBottom() {return body->getBottom();}
float Player::getLeft() {return body ->getLeft();}
float Player::getRight() {return body->getRight();}












