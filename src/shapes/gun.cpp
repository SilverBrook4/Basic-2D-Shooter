#include "gun.h"

Gun::Gun(Shader &shader, vec2 pos, vec2 size, struct ::color color) : Shape(shader, pos, (size * 6.0f), color) {
    initVectors();
    initVAO();
    initVBO();
    initEBO();
}

Gun::Gun(Gun const &other) : Shape(other) {
    initVectors();
    initVAO();
    initVBO();
    initEBO();
}


Gun::~Gun() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Gun::initVectors() {
    // creates vertices shifted to the right of a normal Rect
    this->vertices.insert(vertices.end(), {
        0.0f, 0.5f, // top left
        1.0f, 0.5f, // top right
        0.0f, -0.5f, // bottom left
        1.0f, -0.5f, // bottom right
    });
    // fors the triangles that make up the Gun
    this->indices.insert(indices.end(), {
        0, 1, 2, // triangle 1
        1, 2, 3, // triangle 2
    });
}


float Gun::getLeft() const      {return pos.x;}
float Gun::getRight() const     {return pos.x + size.x;}
float Gun::getTop() const       {return pos.y + (size.y / 2);}
float Gun::getBottom() const    {return pos.y - (size.y / 2);}

void Gun::draw() const {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


