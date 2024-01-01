#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath> 
#include <iostream> 

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;
const float ballRadius = 5.0f;
const float simulationSpeed = 4.0f;
const float spawnInterval = 1.0f;
const float dumpingConstant = 0.5f;

class Ball {
public:
    Ball(float x, float y, float vx, float vy)
        : position(x, y), velocity(vx, vy) {
        shape.setRadius(ballRadius);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Blue);
        drawColor = sf::Color::Blue;
    }

    void update(float delta) {
        position += velocity * delta;
        shape.setPosition(position);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const {
        return position;
    }

    void setPosition(float x, float y){

        sf::Vector2f position;
        position.x = x;
        position.y = y;
        shape.setPosition(position);
    }

    void applyImpulse(const sf::Vector2f& impulse) {
        velocity += impulse;
    }

    void boundsColision(float x, float y){
        velocity.x *= x;
        velocity.y *= y;
    }

    void applyGravity(float gravity, float delta){
        velocity.y += gravity * delta;
    }

    void move(float x, float y) {
        sf::Vector2f position = shape.getPosition();
        position.x += x;
        position.y += y;
        shape.setPosition(position);
    }

    sf::Color drawColor; 
    sf::CircleShape shape;
    float radius;

private:

    sf::Vector2f position;
    sf::Vector2f velocity;
};

class BallManager {
public:
    void spawnBall() {
        float x = 20.0f + ballRadius;
        float y = 20.0f + ballRadius;
        float vx = 300.0f; 
        float vy = 0.0f;
        float radius = ballRadius;
        balls.push_back(Ball(x, y, vx, vy));
    }

    void update(float delta) {
        for (auto& ball : balls) {
            ball.applyGravity(20.0, delta);
            ball.update(delta);
            ball.shape.setFillColor(ball.drawColor);
        }

        // Check collisions
        detectCollisions(delta);
    }

    void update_sub_steps(float dt, int sub_steps){
        const float sub_dt = dt / float(sub_steps);
        for (int i = 0; i < sub_dt; i++) {
            update(dt);
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& ball : balls) {
            window.draw(ball.shape);
        }
    }

private:
    void detectCollisions(float delta);
    void handleCollision(Ball& ballA, Ball& ballB, const sf::Vector2f& dist, float distance, float delta);


    std::vector<Ball> balls;
};


void BallManager::detectCollisions(float delta) {
    for (size_t i = 0; i < balls.size(); ++i) {
            // Check collisions with boundaries
            if (balls[i].getPosition().x + ballRadius > SCREEN_WIDTH) {
                balls[i].setPosition(SCREEN_WIDTH - ballRadius, balls[i].getPosition().y);
                balls[i].boundsColision(-1 * dumpingConstant, 1);
            } else if (balls[i].getPosition().x - ballRadius < 0) {
                balls[i].setPosition(0.0 + ballRadius, balls[i].getPosition().y);
                balls[i].boundsColision(-1 * dumpingConstant, 1);
            }

            if (balls[i].getPosition().y + ballRadius > SCREEN_HEIGHT) {
                balls[i].setPosition(balls[i].getPosition().x, SCREEN_HEIGHT - ballRadius);
                balls[i].boundsColision(-1 * dumpingConstant, 1);
                balls[i].boundsColision(1, -1 * dumpingConstant);
            } else if (balls[i].getPosition().y - ballRadius < 0) {
                balls[i].setPosition(balls[i].getPosition().x, 0 + ballRadius);
                balls[i].boundsColision(1, -1 * dumpingConstant);
            }


        for (size_t j = i + 1; j < balls.size(); ++j) {
            sf::Vector2f dist = balls[j].getPosition() - balls[i].getPosition();
            float distance = std::sqrt(dist.x * dist.x + dist.y * dist.y);

            if (distance < balls[i].radius + balls[j].radius) {
                // Collision detected, you can add your logic here
                // For example, change colors, velocities, etc.
                balls[i].drawColor = sf::Color::Red;
                balls[j].drawColor = sf::Color::Red;

                // Call a separate function to handle collision response
                handleCollision(balls[i], balls[j], dist, distance, delta);
            }
        }
    }
}

void BallManager::handleCollision(Ball& ballA, Ball& ballB, const sf::Vector2f& dist, float distance, float delta) {
    // Reverse velocities in opposite directions

    float x = ballA.getPosition().x - ballB.getPosition().x;
    float y = ballA.getPosition().y - ballB.getPosition().y;
    // float distance = std::sqrt(std::pow(x,2.0f) + std::pow(y, 2.0f));
    float theta = std::atan(y/x);
    printf("%f\n", theta);
    float deltaDist = ((ballA.radius + ballB.radius) - distance) / 2.0f;
    ballA.move(-deltaDist * std::cos(theta), deltaDist * std::sin(theta));
    ballB.move(deltaDist * std::cos(theta), - deltaDist * std::sin(theta));
}


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Ball Collision");
    BallManager ballManager;

    sf::Clock clock;
    sf::Clock fpsClock;
    float spawnTimer = 0.0f;
    int frameCount = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        float delta = clock.restart().asSeconds() * simulationSpeed;
        spawnTimer += delta;

        if (spawnTimer >= spawnInterval) {
            ballManager.spawnBall();
            spawnTimer = 0.0f;
        }

        ballManager.update_sub_steps(delta, 8);

        window.clear();
        ballManager.draw(window);
        window.display();

        // // FPS calculation
        // frameCount++;
        // if (fpsClock.getElapsedTime().asSeconds() >= 1.0) {
        //     // Display FPS in console (you can modify this part based on your needs)
        //     std::cout << "FPS: " << frameCount << std::endl;

        //     // Reset counters
        //     frameCount = 0;
        //     fpsClock.restart();
        // }
    }

    return 0;
}
