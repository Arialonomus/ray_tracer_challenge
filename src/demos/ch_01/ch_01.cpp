/*--------------------------------------------------------------
* Virtual Cannon
* Ray Tracer Challenge - Chapter 1 Demo (Putting It Together)
*
* Implementation by Jacob Barber
----------------------------------------------------------------*/

#include "vector4.hpp"

struct Projectile
{
    gfx::Vector4 position;
    gfx::Vector4 velocity;
};

struct Environment
{
    gfx::Vector4 gravity;
    gfx::Vector4 wind_speed;
};

Projectile tick(Projectile proj, Environment env)
{
    return Projectile{ proj.position + proj.velocity, proj.velocity + env.gravity + env.wind_speed };
}

int main()
{

}