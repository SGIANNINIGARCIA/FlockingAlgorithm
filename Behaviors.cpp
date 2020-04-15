#include "Behaviors.h"



Behaviors::Behaviors(){

}

Behaviors::~Behaviors(){

}


Vector2d
Behaviors::adjustAccForNeighborAvoidance(Agent& curAgent, std::vector<std::shared_ptr<Agent> >& preyAgents){

    double distBetweenCurAndOth;
    std::shared_ptr<Agent> othAgent;
    Vector2d newForce;
    Vector2d desiredDir(0,0);
    Vector2d diffDir(0,0);

    for (unsigned i=0; i<preyAgents.size(); ++i) {

        othAgent = preyAgents[i];
        distBetweenCurAndOth = curAgent.getPos()->distance(*othAgent->getPos());

        if ((distBetweenCurAndOth > 0) &&
                (distBetweenCurAndOth < Flocking::MIN_AVOID_DIST)) {
            // Find vector pointing away from the other agents
            // and weight by distance
            diffDir = *curAgent.getPos() - *othAgent->getPos();
            diffDir.makeUnitVector();
            diffDir = diffDir / distBetweenCurAndOth;
            desiredDir = desiredDir + diffDir;

        }
    }

    if (desiredDir.length() > 0) {
        // Set average vector to the length of the desired speed
        desiredDir.makeUnitVector();
        desiredDir = desiredDir * Flocking::DESIRED_SPEED;
        // Reynolds defined steering force as: desired vel - curr vel
        newForce = desiredDir - curAgent.getVel();
        limitForce(newForce);
        return newForce;
    }

    return desiredDir;
}

Vector2d
Behaviors::adjustAccForObstacleAvoidance(Agent& curAgent, std::vector<std::shared_ptr<Obstacle> >& obstacles){

    double distBetweenCurAndOth;
    std::shared_ptr<Obstacle> currObstacle;
    Vector2d newForce;
    Vector2d desiredDir(0,0);
    Vector2d avoidanceForce(0,0);
    std::shared_ptr<Obstacle> mostThreatening = std::make_shared<Obstacle>(0 ,
                                                                           0, 0,
                                                                           "obstacle", 0);

    curAgent.getVel().makeUnitVector();
    Vector2d aheadVector(curAgent.getPos()->getX() +
                         (curAgent.getVel().getX() * Flocking::MAX_SEE_AHEAD_DISTANCE),
                         curAgent.getPos()->getY() +
                         (curAgent.getVel().getY() * Flocking::MAX_SEE_AHEAD_DISTANCE));

    Vector2d aheadNoneVector(curAgent.getPos()->getX(), curAgent.getPos()->getY());

    Vector2d aheadHalfVector(curAgent.getPos()->getX() +
                             ((curAgent.getVel().getX() * Flocking::MAX_SEE_AHEAD_DISTANCE)/2),
                         curAgent.getPos()->getY() +
                             ((curAgent.getVel().getY() * Flocking::MAX_SEE_AHEAD_DISTANCE)/2));

    Vector2d diffDir(0,0);

    for (unsigned i=0; i<obstacles.size(); ++i) {

        currObstacle = obstacles[i];

        //if(collision(aheadVector, aheadHalfVector, aheadNoneVector, *currObstacle)
          //      && (curAgent.getPos()->distance(*currObstacle->getPos())) < curAgent.getPos()->distance(*mostThreatening->getPos())){

            //mostThreatening = currObstacle;
        //}

    }

    if(mostThreatening == NULL){
        return desiredDir;
    }

    avoidanceForce = aheadVector - *mostThreatening->getPos();
    avoidanceForce.makeUnitVector();
    avoidanceForce = avoidanceForce * Flocking::MAX_AVOID_FORCE;
    desiredDir = avoidanceForce;
    desiredDir.makeUnitVector();
    desiredDir = desiredDir * Flocking::DESIRED_SPEED;
    newForce = desiredDir - curAgent.getVel();
    limitForce(newForce);

    return newForce;


}

Vector2d
Behaviors::adjustAccForFleeing(Agent& curAgent, std::vector<std::shared_ptr<Agent> >& predatorAgents){

    double distBetweenCurAndOth;
    std::shared_ptr<Agent> othAgent;
    Vector2d newForce;
    Vector2d desiredDir(0,0);
    Vector2d diffDir(0,0);

    for (unsigned i=0; i<predatorAgents.size(); ++i) {

        othAgent = predatorAgents[i];
        distBetweenCurAndOth = curAgent.getPos()->distance(*othAgent->getPos());

        if ((distBetweenCurAndOth > 0) &&
                (distBetweenCurAndOth < 400)) {
            diffDir = *curAgent.getPos() - *othAgent->getPos();
            diffDir.makeUnitVector();
            desiredDir = desiredDir + diffDir;
        }
    }

    if (desiredDir.length() > 0) {
        // Set average vector to the length of the desired speed
        desiredDir.makeUnitVector();
        desiredDir = desiredDir * Flocking::MAX_AVOID_FORCE;
        // Reynolds defined steering force as: desired vel - curr vel
        newForce = desiredDir - curAgent.getVel();
        limitForce(newForce);
        return newForce;
    }

    return desiredDir;

}

Vector2d
Behaviors::adjustAccForNeighborPosition(Agent& curAgent, std::vector<std::shared_ptr<Agent> >& preyAgents){
    double distBetweenCurAndOth;
    std::shared_ptr<Agent> othAgent;
    Vector2d newForce;
    Vector2d desiredPosition(0,0);
    Vector2d diffDir(0,0);

    int numOfClosePreys = 0;

    for (unsigned i=0; i<preyAgents.size(); ++i) {

        othAgent = preyAgents[i];
        distBetweenCurAndOth = curAgent.getPos()->distance(*othAgent->getPos());

        if ((distBetweenCurAndOth > 0) &&
                (distBetweenCurAndOth < Flocking::MIN_AVOID_DIST)) {

            diffDir = *othAgent->getPos();
            desiredPosition = desiredPosition + diffDir;
            numOfClosePreys++;
        }
    }

    if(numOfClosePreys == 0){
        return desiredPosition;
    }

    desiredPosition = (desiredPosition / numOfClosePreys);
    desiredPosition = desiredPosition - *curAgent.getPos();


    if (desiredPosition.length() > 0) {
        // Set average vector to the length of the desired speed
        desiredPosition.makeUnitVector();
        desiredPosition = desiredPosition * Flocking::DESIRED_SPEED;
        // Reynolds defined steering force as: desired vel - curr vel
        newForce = desiredPosition - curAgent.getVel();
        limitForce(newForce);
        return newForce;
    }
    return desiredPosition;

}

Vector2d
Behaviors::adjustAccForNeighborVelocity(Agent& curAgent,std::vector<std::shared_ptr<Agent> >& preyAgents){

    double distBetweenCurAndOth;
    std::shared_ptr<Agent> othAgent;
    Vector2d newForce;
    Vector2d desiredVel(0,0);

    for (unsigned i=0; i<preyAgents.size(); ++i) {

        othAgent = preyAgents[i];
        distBetweenCurAndOth = curAgent.getPos()->distance(*othAgent->getPos());

        if ((distBetweenCurAndOth > 0) &&
                (distBetweenCurAndOth < Flocking::MIN_AVOID_DIST)) {
            // add all velocities
            desiredVel = desiredVel + curAgent.getVel();
        }
    }
    if (desiredVel.length() > 0) {
        // Set average vector to the length of the desired speed
        desiredVel.makeUnitVector();
        desiredVel = desiredVel * Flocking::DESIRED_SPEED;
        // Reynolds defined steering force as: desired vel - curr vel
        newForce = desiredVel - curAgent.getVel();
        limitForce(newForce);
        return newForce;
    }

    return desiredVel;
}

void
Behaviors::limitForce(Vector2d& force){
    double MaxForce = 0.05;

    if (force.length() > MaxForce) {
        force.makeUnitVector();
        force = force * MaxForce;
    }
}

bool
Behaviors::collision(Vector2d ahead, Vector2d half, Vector2d none, Obstacle& obstacle){

    if(ahead.distance(*obstacle.getPos()) < obstacle.getRadius()){
        return true;
    } else if (half.distance(*obstacle.getPos()) < obstacle.getRadius()){
        return true;
    } else if (none.distance(*obstacle.getPos()) < obstacle.getRadius()){
        return true;
    } else {
        return false;
    }
}
