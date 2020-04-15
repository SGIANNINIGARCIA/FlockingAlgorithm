#include "Obstacle.h"

Obstacle::Obstacle(int x,int y, double heading, std::string type, float radius){
    m_x          = x;
    m_y          = y;
    m_heading    = heading;
    m_type       = type;
    m_radius     = radius;
    m_pos        = Vector2d(x, y);
}

float
Obstacle::getRadius(){
    return m_radius;
}

void
Obstacle::setRadius(float radius){
    m_radius = radius;
}
