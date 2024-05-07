#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(double x, double y)
{
    this->x = x;
    this->y = y;
    dx = 0;
    dy = 0;
}
PhysicsObject::PhysicsObject()
{
    x = 0;
    y = 0;
    dx = 0;
    dy = 0;
}
double PhysicsObject::accelerate(double dt, double acceleration)
{
    // speed = dx/dt acceleration(units/s)^2
    dx = acceleration/dt;
    return dx;
}
