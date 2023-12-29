#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath> 

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;
const float ballRadius = 20.0f;
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

    sf::Color drawColor; 
    sf::CircleShape shape;

private:

    sf::Vector2f position;
    sf::Vector2f velocity;
};

class BallManager {
public:
    void spawnBall() {
        float x = 20.0f + ballRadius;
        float y = 20.0f + ballRadius;
        float vx = 200.0f; 
        float vy = 0.0f;
        balls.push_back(Ball(x, y, vx, vy));
    }

    void update(float delta) {
        for (auto& ball : balls) {
            ball.applyGravity(20.0, delta);
            ball.update(delta);
        }

        // Check collisions
        detectCollisions(delta);
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

            if (distance < 2 * ballRadius) {
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
    sf::Vector2f collisionNormal = dist / distance;
    sf::Vector2f relativeVelocity = ballB.getPosition() - ballA.getPosition();
    float dotProduct = relativeVelocity.x * collisionNormal.x + relativeVelocity.y * collisionNormal.y;
    sf::Vector2f impulse = (2.0f * dotProduct / (1.0f + 1.0f)) * collisionNormal;

    ballA.applyImpulse(impulse*delta*dumpingConstant);
    ballB.applyImpulse(-impulse*delta*dumpingConstant);
    float overlap = 2 * ballRadius - distance;
    sf::Vector2f correction = 0.5f * overlap * collisionNormal;

    ballA.shape.move(correction);
    ballB.shape.move(-correction);
}
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Ball Collision");
    BallManager ballManager;

    sf::Clock clock;
    float spawnTimer = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }
        }

        float delta = clock.restart().asSeconds() * simulationSpeed;
        spawnTimer += delta;

        if (spawnTimer >= spawnInterval) {
            ballManager.spawnBall();
            spawnTimer = 0.0f;
        }

        ballManager.update(delta);

        window.clear();
        ballManager.draw(window);
        window.display();
    }

    return 0;
}
