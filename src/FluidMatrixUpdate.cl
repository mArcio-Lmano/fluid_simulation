// FluidMatrixUpdate.cl

// Define constants
#define GRAVITY 500.0f
#define DELTA_TIME 0.016f
#define Y_TOP 200.0f
#define Y_BOT 880.0f
#define DAMPING_CONST 0.9f

// Kernel function to update the FluidMatrix
__kernel void fluidMatrixUpdate(__global float2* velocities,
                                __global float2* positions,
                                const int rows,
                                const int cols) {
    int i = get_global_id(0);
    int j = get_global_id(1);

    // Update velocity based on gravity
    velocities[i * cols + j].y += GRAVITY * DELTA_TIME;

    // Update position based on velocity
    positions[i * cols + j].y += velocities[i * cols + j].y * DELTA_TIME;

    // Check if the circle is out of bounds in the y direction
    if (positions[i * cols + j].y > Y_BOT) {
        // Bounce back by reversing the y velocity
        positions[i * cols + j].y = Y_BOT;
        velocities[i * cols + j].y *= -1 * DAMPING_CONST;
    } else if (positions[i * cols + j].y < Y_TOP) {
        // Bounce back by reversing the y velocity
        positions[i * cols + j].y = Y_TOP;
        velocities[i * cols + j].y *= -1 * DAMPING_CONST;
    }
}
