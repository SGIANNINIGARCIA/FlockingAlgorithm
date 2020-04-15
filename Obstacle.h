#pragma once

#include "Agent.h"

class Obstacle : public Agent
{
    Q_OBJECT

private:
    float m_radius;

public:
    Obstacle(int x,
             int y,
             double heading,
             std::string type,
             float radius);
    Obstacle(){};
   ~Obstacle() {}

    float getRadius();
    void setRadius(float);

    // Add setters and getters here
    // ...
};
