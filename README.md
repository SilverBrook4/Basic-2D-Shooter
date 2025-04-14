# Basic 2D Shooter
### By: Mason Ritchie 

## Summary:
This project is designed to act as the base functionality of a 2D top-down shooter written in C++. It is designed
It will be scaled up later into a larger game when I have more time to develop gameplay functionality.
The game itself has a character that can move around the screen and fire bullets out of its gun. 
Around the play area are green targets that, when hit, become more and more see-through till they are
all the way see through and are removed from the game. When all of the targets have been destroyed
the player wins the game. New bullets are spawned each time the player shoots and are then removed
once they encounter a collision or go off-screen. Bullets are created as a child class of the Projectile
class that stores the important info for a projectile, and the child classes store the hit boxes, hit
points, and shapes that make up the render of it. This will allow for easy expansion of the types of
projectiles used in future iterations of this game.
### Controls:
* Movement:
  * W / Up Arrow
    * moves character up
  * s / Down Arrow
    * moves character down
  * A / Left Key
    * moves character to the left
  * D / Right Key
    * moves character to the right
* Shooting:
  * Mouse
    * character aim follows the mouse
  * Left Mouse Click
    * fires bullet
* Other:
  * ESC
    * exits the game

## Installations / Technologies Used:
* C++
* OpenGL
* GLAD
* GLFW
* GLM

## Future Plans:
* change collision detection to use OBB and more use of the hitboxes I added
  * currently uses it points because they were easier to implement for rotated shape collisions and the initial timeline on this project
* abstract enemies into their own class
  * add movment
  * add combat ai
  * add colision with player(left out due to time and currently only serving as targets so where unneeded)
* expand the player class
  * health
  * ammo
* add a score system with maybe a leader board saved to a file
* add more projectile types
* add walls in game that can be collided with
* create a start and end screen with controls listed
* add either different rooms or levels

## Citations / Sources:
The base of the engine class, shape class, rect class, circle class, color struct, debug.h, and everything in shader was
created by Lisa Dion acts as the base that I built everything else on. They act as the basic setup to make a window and run the
processes to run the code. I made modifications to the circle class and all of the gameplay I wrote in the engine class.

      * custom shape based off of the rectangle class but with a shifted center to the middle
      of the left edge for simpler rotation mechanics for aiming.




