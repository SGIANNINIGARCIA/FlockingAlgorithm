#pragma once

#include "Agent.h"
#include "Obstacle.h"
#include "Constants.h"
#include <iostream>
#include <memory>

class Behaviors
{

private:
    void limitForce(Vector2d&);
    bool collision(Vector2d, Vector2d, Vector2d, Obstacle&);

public:
    Behaviors();
   ~Behaviors();

    Vector2d adjustAccForNeighborAvoidance(
            Agent& curAgent,
            std::vector<std::shared_ptr<Agent> >& preyAgents);
    Vector2d adjustAccForObstacleAvoidance(
            Agent& curAgent,
            std::vector<std::shared_ptr<Obstacle> >& obstacles);
    Vector2d adjustAccForFleeing(
            Agent& curAgent,
            std::vector<std::shared_ptr<Agent> >& predatorAgents);
    Vector2d adjustAccForNeighborPosition(
            Agent& curAgent,
            std::vector<std::shared_ptr<Agent> >& preyAgents);
    Vector2d adjustAccForNeighborVelocity(
            Agent& curAgent,
            std::vector<std::shared_ptr<Agent> >& preyAgents);

};
