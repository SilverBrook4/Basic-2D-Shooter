#include "engine.h"
#include <iostream>


Engine::Engine() : keys() {
    this->initWindow();
    this->initShaders();
    this->initShapes();
}

Engine::~Engine() {}

unsigned int Engine::initWindow(bool debug) {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    // This creates the window using GLFW.
    // It's a C function, so we have to pass it a pointer to the window variable.
    window = glfwCreateWindow(width, height, "engine", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    // This sets the OpenGL context to the window we just created.
    glfwMakeContextCurrent(window);

    // Glad is an OpenGL function loader. It loads all the OpenGL functions that are defined by the driver.
    // This is required because OpenGL is a specification, not an implementation.
    // The driver is the implementation of OpenGL that is installed on your computer.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // OpenGL configuration
    // This defines the size of the area OpenGL should render to.
    glViewport(0, 0, width, height);
    // This enables depth testing which prevents triangles from overlapping.
    glEnable(GL_BLEND);
    // Alpha blending allows for transparent backgrounds.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);

    return 0;
}

void Engine::initShaders() {
    // load shader manager
    shaderManager = make_unique<ShaderManager>();

    // Load shader into shader manager and retrieve it
    shapeShader = this->shaderManager->loadShader("../res/shaders/shape.vert",
                                                  "../res/shaders/shape.frag",
                                                  nullptr, "shape");

    // Set uniforms that never change
    shapeShader.use().setMatrix4("projection", this->PROJECTION);
}

void Engine::initShapes() {
    // creates player
    player = make_unique<Player>(shapeShader, vec2(width / 2, height / 2), 3.0f, color(1, 0, 0, 1));

    // creates shapes
    enemies.push_back(make_unique<Rect>(shapeShader, vec2(100, 100), vec2(30, 30), color(0, 1, 0, 1)));
    enemies.push_back(make_unique<Rect>(shapeShader, vec2(700, 500), vec2(30, 30), color(0, 1, 0, 1)));
    enemies.push_back(make_unique<Rect>(shapeShader, vec2(600, 150), vec2(30, 30), color(0, 1, 0, 1)));
    enemies.push_back(make_unique<Rect>(shapeShader, vec2(175, 500), vec2(30, 30), color(0, 1, 0, 1)));
    enemies.push_back(make_unique<Rect>(shapeShader, vec2(300, 230), vec2(30, 30), color(0, 1, 0, 1)));
    enemies.push_back(make_unique<Rect>(shapeShader, vec2(400, 500), vec2(30, 30), color(0, 1, 0, 1)));
    enemies.push_back(make_unique<Rect>(shapeShader, vec2(700, 340), vec2(30, 30), color(0, 1, 0, 1)));
}

void Engine::processInput() {
    glfwPollEvents();

    // Set keys to true if pressed, false if released
    for (int key = 0; key < 1024; ++key) {
        if (glfwGetKey(window, key) == GLFW_PRESS)
            keys[key] = true;
        else if (glfwGetKey(window, key) == GLFW_RELEASE)
            keys[key] = false;
    }

    // Close window if escape key is pressed
    if (keys[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, true);

    // saves mouses position
    glfwGetCursorPos(window, &MouseX, &MouseY);

    //makes sure y-axis isnt flipped
    MouseY = height - MouseY;

    // Calculate delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // start of controls

    // movement keys (w, s, a, d, arrows) and ensures movment doesnt go out of bounds
    if ((player->getPosY() + player->getRadius() * 6.75) < height) { // move up
        if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
            player->moveY(player->getSpeed());
            if (player->getPosY() + (player->getRadius() * 6.75) > height) {
                player->setPosY(height - player->getRadius() * 6.75);
            }
        }
    }
    if ((player->getPosY() - player->getRadius() * 6.75) > 0) { // move down
        if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
            player->moveY(-player->getSpeed());
            if (player->getPosY() - player->getRadius() * 6.75 < 0) {
                player->setPosY(player->getRadius() * 6.75);
            }
        }
    }
    if (player->getPosX() - player->getRadius() * 6.75 > 0) {//move left
        if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
            player->moveX(-player->getSpeed());
            if (player->getPosX() - player->getRadius() * 6.75 < 0) {
                player->setPosX(player->getRadius() * 6.75);
            }
        }
    }
    if (player->getPosX() + player->getRadius() * 6.75 < width) { // move right
        if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
            player->moveX(player->getSpeed());
            if (player->getPosX() + player->getRadius() * 6.75 > width) {
                player->setPosX(width - player->getRadius() * 6.75);
            }
        }
    }

    // fire key (left mouse)
    bool leftMousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    if (leftMousePressedLastFrame && !leftMousePressed) {
        // spawns projectile
        playerProjectiles.push_back(move(make_unique<Bullet>(shapeShader, vec2(player->getPosX(), player->getPosY()), 2.0f, aimSlope, 1.0f, deltaTime)));
    }

    // checks if mouse button pressed last frame
    leftMousePressedLastFrame = leftMousePressed;
}

void Engine::update() {
    // Calculate delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // sets aim slope
    aimSlope.x = MouseX - player->getPosX();
    aimSlope.y = MouseY - player->getPosY();

    // checks for collisions
    int countE = 0;
    int countP = 0;
    vector<int> projectileCollisionCount;
    vector<int> enemieDeathCount;
    for (unique_ptr<Projectile>& p : playerProjectiles) {
        for (unique_ptr<Rect>& e : enemies) {
            // compares objects to see if there is collision
            if (detectProjectileCollision(p ,e)) {
                // reduces opacity of hit enemie
                e->setOpacity(e->getOpacity() - 0.1f);

                // stores indeces of objects collsisions for later removal
                projectileCollisionCount.insert(projectileCollisionCount.begin(), countP);
                // checks if enemies have lost enough health (opacity) to be removed from play
                if (e->getOpacity() < 0) {
                    enemieDeathCount.insert(enemieDeathCount.begin(), countE); // marks dead enemies for deletion
                }
            }
            ++countE;
        }
        // checks if bullet is in play bounds
        if ((p->getPos().x < -10) || (p->getPos().x > width + 10) || (p->getPos().y < -10) || (p->getPos().y > height + 10)) {
                projectileCollisionCount.insert(projectileCollisionCount.begin(), countP); // marks bullet out of bounds for deletion
        }
        countE = 0;
        ++countP;
    }

    // removes used projectiles
    for (int i : projectileCollisionCount) {
        playerProjectiles.erase(playerProjectiles.begin() + i);
    }

    // removes dead enemies
    for (int i : enemieDeathCount) {
        enemies.erase(enemies.begin() + i);
    }

    // player rotates gun to follow mouse
    player->setRotation(atan2(aimSlope.y, aimSlope.x) * (180/M_PI), deltaTime);

    // move projectiles
    for (const unique_ptr<Projectile>& p : playerProjectiles) {
        p->move();
    }

    // checks for all enemies dead win condition
    if (enemies.size() == 0) {
        glfwSetWindowShouldClose(window, true);
    }

    // This function polls for events like keyboard input and mouse movement
    // It needs to be called every frame
    // Without this function, the window will freeze and become unresponsive
    glfwPollEvents();
}

void Engine::render() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // render bullets
    for (const unique_ptr<Projectile>& p : playerProjectiles) {
        p->setUniformsAndDraw();
    }

    // render enemies
    for (const unique_ptr<Rect>& r : enemies) {
        r->setUniforms();
        r->draw();
    }

    // renders player
    player->setUniformsAndDraw();

    // This is glfw function call is required to display the final image on the screen
    // The front buffer contains the final image that is displayed.
    // The back buffer contains the image that is currently being rendered.
    glfwSwapBuffers(window);
}

bool Engine::shouldClose() {
    return glfwWindowShouldClose(window);
}

bool Engine::detectProjectileCollision(unique_ptr<Projectile>& p, unique_ptr<Rect>& b) {
    for (Point point : p->getHitPoints()) {
        if ((b->getLeft() <= point.x) && (point.x <= b->getRight())) { // checks if p is in x bounds
            if ((b->getBottom() <= point.y) && (point.y <= b->getTop())) { // checks if p is in y bounds
                return true; // collision detected
            }
        }
    }
    return false; // no collision detected
}

