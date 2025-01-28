#include "rendering_functions.hpp"

namespace rt {
    const rt::Canvas render(const gfx::World& world, const rt::Camera& camera)
    {
        rt::Canvas image{ camera.getViewportWidth(), camera.getViewportHeight() };

        // Cast a ray to determine the color for each pixel in the viewport
        for (int y = 0; y < camera.getViewportHeight(); ++y)
            for (int x = 0; x < camera.getViewportWidth(); ++x) {
                image[x, y] = world.calculatePixelColor(camera.castRay(x, y));
            }

        return image;
    }
}