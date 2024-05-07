#pragma once

class PhysicsObject
{
private:
    double x;
    double y;
    double dx;
    double dy;
public:
    PhysicsObject(double x, double y);
    PhysicsObject();

    double accelerate(double dt, double acceleration);
};

