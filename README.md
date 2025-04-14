# Basic Shooter: Target Practice
### By: Mason Ritchie (mritchi1)

## Installation Dependencies:
* OpenGL
* GLFW
* GLM
* GLAD

## Summary:
This project is designed to act as the base functionality of a 2D top down shooter. It is designed
to be later scaled up into a larger game if given more time to develop more gameplay functionality.
The game itself has a character that can move around the screen and fire bullets out of its gun. 
Around the play area are green targets that when hit become more and more see through till they are
all the way see through and are removed from the game. when all of the targets have been destroyed
the player wins the game. new bullets are spawned each time the player shoots and are then removed
once they encounter a collision or go off screen. Bullets are created as a child class of the Projectile
class which stores the important info for a projectile and the child classes store the hit boxes, hit
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

## Bugs:
* No known bugs

## Future Plans:
* change collision detection to use OBB and more use of the hitboxes I added
  * currently uses it points because they were easier to implement for rotated shape collisions and time
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

These will likely be implemented in the final project for this.

## Citations / Sources:
base of program (engine, shapes, rect, ect.) came from the graphics starter repo by Lisa Dion. The
Circle class is also taken from the runner guided project. I made modifications to the engine and
shape class to implement certain functions. The rest of the code was authored by myself.

## Grade:
I think I should receive an A for this project. I belive there is more than enough complexity to meet
this requirment. Objects on screen are managed well and deleted when they become unnecessary. I also 
used many of the module 4 concepts which I will list bellow. There is lots of 
interactivity as to how the user can move the player and fire at targets. There are also events triggered
by the user input and others triggered by certain conditions met later in the program such as bullets 
colliding with targets. The user experience is very smooth with the game following basic shooter control
patterns and smooth control. While the controls are not displayed in the game they are listed in the 
readme and are intuative to figure out. If given more time I would implement controlls being listed in 
the program. all the code is broken into multiple classes based on what it does and various files are
organized across different folders. All code and classes are well documented across their .h and .cpp files.
The project has also had a lifespan across the past 2 weeks.
### Concepts:
* FrameWorks:
  * OpenGl
  * GLFW
  * GLAD
  * GLM
* Drawing:
  * player
  * enemies
  * projectiles
* Keyboard Inputs:
  * W, A, S, D, Left, Right, Up, Down
    * controls player movement
  * ESC
    * closes game
* Mouse Inputs:
  * Left Click
    * fires bullets
  * Mouse Location
    * player aim
* Non-Input Based Events:
  * Movement of bullets across screen
  * Deletion of bullets on collision
  * Changing of targets opacity / health on collision
  * Deletion of targets after certain health loss
* Graphics with Classes:
  * Player
    * Has-a:
      * Circle (body)
      * Gun (gun)
        * a custom rectangle class with its center shifted to the left edge
  * Projectile
    * Bullet
      * Has-a:
        * Shapes (what is rendered always): comprises the bullet
          * Rect (base of bullet)
          * Circle (tip of bullet)
        * HitBox (only rendered when hitbox visibility is turned on)
          * Rect (see through rectangle that shows collision)
  * Shapes
    * Gun
      * custom shape based off of the rectangle class but with a shifted center to the middle
      of the left edge for simpler rotation mechanics for aiming.




