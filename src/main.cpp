#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <iostream>

const float SCREEN_WIDTH = 1920.0f;
const float SCREEN_HEIGHT = 1080.0f;
const float gravity = 9.8f; // Acceleration due to gravity
const float delta_t = 0.001f; // Time step
const int substeps = 8; // Number of substeps per iteration
const float damping = 0.01f;
const float ai_res = 0.99999;
int clock_m = 1000;

struct Ball {
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Ball(float radius, sf::Vector2f position) {
        shape.setRadius(radius);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);
        velocity.x = 200.0f;
        velocity.y = 0.0f;
    }
    
    sf::Vector2f getCirclePos(){
        sf::Vector2f RectPos = shape.getPosition();
        sf::Vector2f offsetCirc(shape.getRadius(), shape.getRadius());
        return RectPos + offsetCirc;
    }

    void move(const sf::Vector2f& offset) {
        // printf("offset (%f, %f)\n", offset.x, offset.y);
        shape.move(offset);
    }

    
};

class BallManager {
public:
    void addBall(float radius, sf::Vector2f position) {
        balls.push_back(Ball(radius, position));
    }

    void update(sf::RenderWindow& window, float delta, float substeps) {
        float sub_delta = delta / float(substeps);
        for (int i = 0; i < substeps; ++i) {
            for (auto& ball : balls) {
            // Simulate physics with sub-steps
                // Update position based on velocity
                ball.shape.move(ball.velocity * sub_delta);

                // Air Resistance
                // Air Resistance (Damping)
                ball.velocity *= (1.0f - damping * sub_delta);

                // ball.velocity *= ai_res*sub_delta;

                // Update velocity based on gravity
                ball.velocity.y += gravity * sub_delta;

                printf("Ball Velocity: ( %f, %f)\n", ball.velocity.x, ball.velocity.y);

                sf::Vector2f ball_pos = ball.getCirclePos();
                float radius = ball.shape.getRadius();

                if (ball_pos.x + radius >= SCREEN_WIDTH || 
                    ball_pos.x - radius <= 0.0f) {
                    ball.velocity.x = 0.0f;
                }

                if (ball_pos.y + radius >= SCREEN_HEIGHT) {
                    ball.velocity.y = 0.0f;
                }

                // Clamp the position to stay within the screen boundaries
                sf::Vector2f ballPosition = ball.shape.getPosition();
                ballPosition.x = clamp(ballPosition.x, 0.0f, window.getSize().x - 2 * ball.shape.getRadius());
                ballPosition.y = clamp(ballPosition.y, 0.0f, window.getSize().y - 2 * ball.shape.getRadius());
                ball.shape.setPosition(ballPosition);
            }
            check_collision(delta);
        }
    }


    void draw(sf::RenderWindow& window) {
        for (const auto& ball : balls) {
            window.draw(ball.shape);
        }
    }


    void check_collision(float delta) {
        // Check for collisions between each pair of balls
        for (size_t i = 0; i < balls.size(); ++i) {
            for (size_t j = i + 1; j < balls.size(); ++j) {
                sf::Vector2f pos1 = balls[i].getCirclePos();
                sf::Vector2f pos2 = balls[j].getCirclePos();
                float distance = std::sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) +
                                        (pos1.y - pos2.y) * (pos1.y - pos2.y));

                float totalRadius = balls[i].shape.getRadius() + balls[j].shape.getRadius();
                // If the distance between the centers of two balls is less than their combined radii, they collide
                if (distance < totalRadius) {
                    // printf("Colision\n");
                    // printf("Distance %f\n", distance);
                    handle_colision(balls[i], balls[j], distance, delta);

                }
            }
        }
    }

    // void handle_colision(Ball& ballA, Ball& ballB, float distance, float delta){

    //     float delta_d = (ballA.shape.getRadius() + ballB.shape.getRadius() - distance) / 2.0f;
    //     float x = ballA.getCirclePos().x - ballB.getCirclePos().x;
    //     float y = ballA.getCirclePos().y - ballB.getCirclePos().y;
    //     float theta = std::atan2(x, y);

    //     float repulsion_factor = 5.0f;  // Adjust this factor to control the strength of repulsion
    //     float move_factor = repulsion_factor * delta_d;
    //     ballA.move((-move_factor * std::cos(theta)) * delta, (move_factor * std::sin(theta)) * delta);
    //     ballB.move((move_factor * std::cos(theta)) * delta, (-move_factor * std::sin(theta)) * delta);

    //     printf("Velocidade x: %f  Velocidade y: %f, Radious: %f\n", (-delta_d * std::cos(theta))*delta, (delta_d * std::sin(theta))*delta, ballA.shape.getRadius());
    // }


    void handle_colision(Ball& ballA, Ball& ballB, float distance, float delta) {
        constexpr float response_coef = 3.0f;
        constexpr float eps = 0.0001f;

        // Calculate the overlap
        float delta_d = (ballA.shape.getRadius() + ballB.shape.getRadius() - distance) / 2.0f;

        // printf("Overlaap: %f ",delta_d);
        // printf("Distance: %f\n", distance);

        // Check if the particles are overlapping (avoid division by zero)
        if (distance < (ballA.shape.getRadius() + ballB.shape.getRadius()) && distance > eps) {
            // Calculate the collision vector
            sf::Vector2f col_vec = ((ballA.getCirclePos() - ballB.getCirclePos()))  * 0.5f;
            // printf("Collision Vector: (%f, %f)\n", col_vec.x, col_vec.y);
            sf::Vector2f col_vec_inv = -col_vec;
            // printf("Collision Vector Inverse: (%f, %f)\n", col_vec_inv.x, col_vec_inv.y);
    
            // Adjust particle positions based on the collision vector
            ballA.move(col_vec * delta * response_coef);
            ballB.move(col_vec_inv * delta * response_coef);
        }
    }
private:
    std::vector<Ball> balls;

    // Clamp function remains the same
    template <typename T>
    T clamp(T value, T min, T max) {
        return std::max(min, std::min(value, max));
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ball Simulation");

    BallManager ballManager;
    ballManager.addBall(20.0f, sf::Vector2f(400.0f, 0.0f));
    ballManager.addBall(15.0f, sf::Vector2f(400.0f, 100.0f));

    std::random_device rd;
    std::mt19937 gen(rd());

    // Define a distribution for floating-point numbers (e.g., between 0.0 and 1.0)
    std::uniform_real_distribution<> distribution(5.0, 25.0);

    int ball_clock = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        ballManager.update(window, delta_t, 8);

        // Generate a random float
        float randomValue = distribution(gen);
        window.clear();
        ballManager.draw(window);
        window.display();
        ball_clock ++;

        if (ball_clock > clock_m){
            ballManager.addBall(randomValue, sf::Vector2f(400.0f, 100.0f));
            ball_clock = 0;
        }
    }

    return 0;
}
