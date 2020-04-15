#include "Agent.h"
#include <random>

Agent::Agent(int x, int y, double heading, std::string type){

    m_x       = x;
    m_y       = y;
    m_pos     = Vector2d(m_x,m_y);
    m_ahead   = Vector2d (m_x + 1, m_y + 1);
    m_acc     = Vector2d(0, 0);
    m_vel     = Vector2d(((double) rand() / (RAND_MAX)) * 2 - 1, ((double) rand() / (RAND_MAX)) * 2 - 1);
    m_heading = heading;
    m_type    = type;

}

Agent::Agent(){

    this->m_x       = 0;
    this->m_y       = 0;
    this->m_heading = 0;
    this->m_type    = "prey";
}

Agent::~Agent(){}

/////////////////SETTERS////////////////
void
Agent::setX(float x){

    this->m_x = x;
}

void
Agent::setY(float y){

    this->m_y = y;

}

void
Agent::setHeading(double heading){

    this->m_heading = heading;

}

void
Agent::setType(std::string type){

    this->m_type = type;

}

void
Agent::setPos(Vector2d p){

    m_pos = p;

}
void
Agent::setVel(Vector2d v){
    m_vel = v;

}
void
Agent::setAcc(Vector2d a){
    m_acc = a;

}
void
Agent::setAhead(Vector2d a){
    m_ahead = a;

}
void
Agent::setAvoidingObstacle(bool a){
    m_avoidingObstacle = a;

}

/////////////////GETTERS////////////////

float
Agent::getX(){

    return m_x;

}

float
Agent::getY(){

    return m_y;

}

double
Agent::getHeading(){

    return m_heading;

}

std::string
Agent::getType(){

    return m_type;

}

Vector2d*
Agent::getPos(){

    return &m_pos;

}

Vector2d
Agent::getVel(){

    return m_vel;

}

Vector2d
Agent::getAcc(){

    return m_acc;

}

Vector2d
Agent::getAhead(){

    return m_ahead;

}

bool
Agent::getAvoidingObstacle(){

    return m_avoidingObstacle;

}

/////////////OTHERS///////////
void
Agent::addToVel(Vector2d &vec) {
    m_vel = m_vel + vec;
}

void
Agent::addToPos(Vector2d &vec) {
    m_pos = m_pos + vec;
}

void
Agent::resetAcc() {
    m_acc = Vector2d(0,0);
}

// You should randomize the starting vel for a nice initial effect
void
Agent::resetVel() {
    this->m_vel = Vector2d(0.1,0.1);
}

void
Agent::stop() {
    m_vel = Vector2d(0,0);
}

void
Agent::steer(Vector2d vec) {
    m_vel = m_vel - vec;
}

bool
Agent::isPredator() {
    return m_type == "predator";
}

void
Agent::testing(){

    std::cout << getPos()->getX() << std::endl;


}


