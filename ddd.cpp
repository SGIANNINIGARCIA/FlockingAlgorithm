Veccc2d Behaviors::adjustAccForObstacleAvoidance(Agent& curAgent,
        std::vector<std::shared_ptr<Obstacle> >& obstacles){
    Veccc2d desiredDir(0,0);
    Veccc2d avoidanceForce(0,0);
    Obstacle* mostThreat;
    double mostTreatDist=0;
    Veccc2d aheadVec(0,0);
    Veccc2d agntVel = curAgent.getMVel();
    Veccc2d agntPos = curAgent.getMPos();
    agntVel.makeUnitVector();
    agntVel.multScalar(MAX_SEEAHEAD_DIST);
    aheadVec=agntPos+agntVel;
    Veccc2d halfAheadVec=aheadVec;
    double halfLenght=halfAheadVec.length();
    halfAheadVec.makeUnitVector();
    halfAheadVec.multScalar(halfLenght/2);
    Veccc2d aheadNonVec=agntPos;
    double dist=0;
    double realDist=0;
    Veccc2d diff(0,0);
    Veccc2d newForce;
    std::vector<std::shared_ptr<Obstacle> >::iterator itr;

    for (itr = obstacles.begin() ; itr != obstacles.end(); itr++){
        Obstacle* obst = itr->get();
        dist=sqrt((obst->getMx()-curAgent.getMx())*(obst->getMx()-curAgent.getMx())
                  + (obst->getMy()-curAgent.getMy())*(obst->getMy()-curAgent.getMy()));
        realDist=dist-obst->getMRadius();

        if(0<dist && realDist<aheadVec.length()){
          if(realDist<mostTreatDist){
              mostThreat=obst;
              mostTreatDist=realDist;
          }
        }

        if(0<dist && realDist<halfAheadVec.length()){
          if(realDist<mostTreatDist){
              mostThreat=obst;
              mostTreatDist=realDist;
          }
        }

        if(0<dist && realDist<aheadNonVec.length()){
          if(realDist<mostTreatDist){
              mostThreat=obst;
              mostTreatDist=realDist;
          }
        }
    }

    Veccc2d mostTVec=mostThreat->getMPos();
    avoidanceForce = aheadVec - mostTVec;
    desiredDir=avoidanceForce;
    desiredDir.makeUnitVector();
    desiredDir.multScalar(DESIRED_SPEED);
    Veccc2d vel=curAgent.getMVel();
    newForce = desiredDir - vel;
    limitForce(newForce);
    return newForce;
}
