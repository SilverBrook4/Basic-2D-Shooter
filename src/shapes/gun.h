#ifndef GUN_H
#define GUN_H

#include "shape.h"
#include "../shader/shader.h"

using glm::vec2, glm::vec3;

class Gun : public Shape{
private:
    /// @brief Initializes the vertices and indices of the Gun
    void initVectors();
public:
    /// @brief Construct a new Gun object which is a Rect with its position shifted the the middle of the left edge
    /// @param shader The shader to use
    /// @param pos The position of the square
    /// @param size The size of the square
    /// @param color The color of the square
    Gun(Shader & shader, vec2 pos, vec2 size, struct color color);

    /// @breif a copy constructor for Gun
    Gun(Gun const& other);

    /// @brief Destroy the Square object and delete it's VAO and VBO
    ~Gun();

    /// @breif getters for the edge of the squares locations
    float getLeft() const override;
    float getRight() const override;
    float getTop() const override;
    float getBottom() const override;

    /// @breif draws the square on the screen
    void draw() const override;
};



#endif //GUN_H
