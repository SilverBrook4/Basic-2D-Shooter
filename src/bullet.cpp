#include "bullet.h"

Bullet::Bullet(Shader &shader, vec2 pos, float velocity, vec2 slope, float scale, float deltaTime) : Projectile(shader, pos, velocity, slope, scale) {
    // add shapes to render bullet
    vec2 offset = vec2((SIZE/2) * cos(direction / (180/M_PI)), (SIZE/2) * sin(direction / (180/M_PI)));
    shapes.push_back(std::make_shared<Circle>(shader, vec2(pos.x + offset.x , pos.y + offset.y), vec2(SIZE / 4, SIZE / 4), color(1, 1, 0, 1)));
    shapes.push_back(std::make_shared<Rect>(shader, pos, vec2(SIZE, SIZE), color(0.5, 0.5, 0.5, 1)));

    // add hitbox
    hitBox.push_back(std::make_shared<Rect>(shader, vec2(((offset.x) / 2) + pos.x,pos.y), vec2(SIZE * 1.5, SIZE), color(0, 0, 1, 0.5)));

    // add hit points
    hitPoints.push_back(Point{shapes[0]->getPosX() + (shapes[0]->getSize().x / 2), shapes[0]->getPosY()});
    hitPoints.push_back(Point{shapes[0]->getPosX(), shapes[0]->getPosY() + (shapes[0]->getSize().y / 2)});
    hitPoints.push_back(Point{shapes[0]->getPosX(), shapes[0]->getPosY() - (shapes[0]->getSize().y / 2)});

    // rotate shapes to correct direction
    for (const shared_ptr<Shape>& s : shapes) {
        s->setRotation(direction, deltaTime);
    }
    // rotates hitbox to correct direction
    for (const shared_ptr<Rect>& b : hitBox) {
        b->setRotation(direction, deltaTime);
    }
}

Bullet::Bullet(Bullet const &other) : Projectile(other) {
    hitPoints = other.hitPoints;
    // makes deep copy of shapes vector
    if (!other.shapes.empty()) {
        for (const shared_ptr<Shape>& s : other.shapes) {
            shapes.push_back(std::shared_ptr<Shape>(s));
        }
    }
    // makes deep copy of hitBox vector
    if (!other.hitBox.empty()) {
        for (const shared_ptr<Rect>& b : other.hitBox) {
            hitBox.push_back(std::shared_ptr<Rect>(b));
        }
    }
}

Bullet::~Bullet() {}


void Bullet::move() {
    // updates location of render
    for (const shared_ptr<Shape>& s : shapes) {
        vec2 posUpdate = vec2(s->getPosX() + (slope.x * velocity), s->getPosY() + (slope.y * velocity));
        s->setPos(posUpdate);
    }

    // updates location of hitbox
    for (const shared_ptr<Rect>& b: hitBox) {
        vec2 posUpdate = vec2(b->getPosX() + (slope.x * velocity), b->getPosY() + (slope.y * velocity));
        b->setPos(posUpdate);
    }

    // updates hit point location
    for (Point& p : hitPoints) {
        p.x += (slope.x * velocity);
        p.y += (slope.y * velocity);
    }

    // updates position vector
    position.x += (slope.x * velocity);
    position.y += (slope.y * velocity);
}


void Bullet::setUniformsAndDraw() {
    // draws the body of the bullet
    for (const shared_ptr<Shape>& s : shapes) {
        s->setUniforms();
        s->draw();
    }

    // draws the hitbox if hitboxes are turned on
    if (SHOWHITBOX) {
        for (const shared_ptr<Rect>& b : hitBox) {
            b->setUniforms();
            b->draw();
        }
    }
}

vector<Point> Bullet::getHitPoints() {return hitPoints;}






