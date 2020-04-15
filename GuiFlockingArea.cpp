#include "GuiFlockingArea.h"
#include "Constants.h"

#include <QPainter>
#include <iostream>
#include <math.h>
#include <memory>
#include <random>
#include "GuiMainWindow.h"

GuiFlockingArea::GuiFlockingArea(QWidget *parent)

{
    m_stop                = true;
    m_numPrey             = 100;

    // testing
    x                     = 1;

    Behaviors             behaviors;
    m_Avoid               = 0.1;
    m_Align               = 0.1;
    m_Approach            = 0.1;
    m_AheadVector         = false;


    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void
GuiFlockingArea::initialize()
{
    //Initialize, also known as reset.
    m_PreyAgents.clear();
    m_Obstacles.clear();
    m_Predators.clear();

    for (int i = 0 ; i < m_numPrey ; i++) {

        m_PreyAgents.push_back(std::make_shared<Agent>(QWidget::width()/2, QWidget::height()/2, 0, "prey"));

    }

}


void
GuiFlockingArea::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}


/**
 * @brief GuiFlockingArea::paintEvent
 *
 * Draws agents into the drawing area.  One way it's called is when
 * update() is called on the object. In this application, update()
 * should be called by the timer that's been set up.
 */
void
GuiFlockingArea::paintEvent(QPaintEvent*)
{

    paintObstacles();
    paintPredators();


    // Create a prey agent with center at origin
    const QPoint preyPoints[4] = {
        QPoint(-3, -5),
        QPoint( 3, -5),
        QPoint( 0,  5),
        QPoint(-3, -5)
    };

    QPen redPen(QColor(255,0,0));
    QPen blackPen(QColor(0,0,0));
    QBrush redBrush(QColor(255,0,0));
    QBrush blackBrush(QColor(0,0,0));

    QPainter painter(this);
    painter.setBrush(brush);

    // Draw one agent's triangle
    // The values in the translate and rotate should come from
    // each agent's instance.  In other words, you'll call these
    // next few lines in a loop over all agents.

    std::vector<std::shared_ptr<Agent> >::iterator it;

    for (it = m_PreyAgents.begin() ; it != m_PreyAgents.end(); ++it){


        // Get current prey from shared pointer and assigned to currAgent
        Agent * currAgent = it->get();

        //apply behaviors
        wrapAround(currAgent);
        updateAgentPosition(currAgent);

        if(m_AheadVector){

            // Circle HW came in handy

            double x = Flocking::MAX_SEE_AHEAD_DISTANCE * cos((currAgent->getHeading() + 90) * Flocking::DEG_TO_RAD );
            double y = Flocking::MAX_SEE_AHEAD_DISTANCE * sin((currAgent->getHeading() + 90) * Flocking::DEG_TO_RAD );
            painter.drawLine(currAgent->getPos()->getX(), currAgent->getPos()->getY(),
                             currAgent->getPos()->getX() + x, currAgent->getPos()->getY() + y);
        }


        painter.save();
        painter.translate(currAgent->getPos()->getX(), currAgent->getPos()->getY());
        painter.rotate(currAgent->getHeading());
        painter.setPen(blackPen);
        painter.setBrush(blackBrush);
        painter.drawPolygon(preyPoints, 4);
        painter.restore();


        // Some misc. drawing commands for the drawing area
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
    }
}

void
GuiFlockingArea::updateAgentPosition(Agent *currAgent){

    if (m_stop) {
        return;
    }


    double heading = 0;
    Vector2d vel(0,0);
    Vector2d finalAcc(0,0);
    Vector2d avoidAcc(0,0);
    Vector2d velAcc(0,0);
    Vector2d posAcc(0,0);
    Vector2d obstAcc(0,0);
    Vector2d predAcc(0,0);

    //avoidance
    avoidAcc = behaviors.adjustAccForNeighborAvoidance(*currAgent,m_PreyAgents);
    avoidAcc = avoidAcc * m_Avoid;


    //velocity
    velAcc = behaviors.adjustAccForNeighborVelocity(*currAgent, m_PreyAgents);
    velAcc = velAcc * m_Align;

    //position
    posAcc = behaviors.adjustAccForNeighborPosition(*currAgent, m_PreyAgents);
    posAcc = posAcc * m_Approach;

    //obstacle
    obstAcc = behaviors.adjustAccForObstacleAvoidance(*currAgent, m_Obstacles);

    //predator
    predAcc = behaviors.adjustAccForFleeing(*currAgent, m_Predators);

    //Total acc
    finalAcc=finalAcc+avoidAcc;
    finalAcc=finalAcc+velAcc;
    finalAcc=finalAcc+posAcc;
    finalAcc=finalAcc+obstAcc;
    finalAcc=finalAcc+predAcc;

    // Update the velocity
    currAgent->addToVel(finalAcc);
    vel = currAgent->getVel();

    // Apply velocity to the position and set heading
    currAgent->addToPos(vel);
    heading = double(atan(vel.getY()/vel.getX()));
    heading = heading/Flocking::DEG_TO_RAD - 90;

    if (vel.getX()< 0) {
        heading += 180;
    }

    currAgent->setHeading(heading);
    currAgent->resetAcc();

}

void
GuiFlockingArea::changeStatus(){

    m_stop = !m_stop;
}

double
GuiFlockingArea::getNumPrey(){

    return m_PreyAgents.size();

}

void
GuiFlockingArea::addPrey(){

    for(int i = 0; i < Flocking::ADD_PREY; i++){
        m_PreyAgents.push_back(std::make_shared<Agent>(QWidget::width()/2, QWidget::height()/2, 0, "prey"));
    }
}

void
GuiFlockingArea::addPredator(){

    m_Predators.push_back(std::make_shared<Agent>(QWidget::width()/2, QWidget::height()/2, 0, "predator"));


}

void
GuiFlockingArea::removePredator(){

    if(m_Predators.size() <= 0){
        return;
    }

    m_Predators.pop_back();

}

int
GuiFlockingArea::getNumObstacles(){
    return m_Obstacles.size();
}

int
GuiFlockingArea::getNumPredators(){
    return m_Predators.size();
}


void
GuiFlockingArea::wrapAround(Agent *currAgent){

    if (currAgent->getPos()->getX() > QWidget::width()){
        currAgent->getPos()->setX(0);
    }

    else if(currAgent->getPos()->getX()  < 0){
        currAgent->getPos()->setX(QWidget::width());
    }

    else if (currAgent->getPos()->getY() > QWidget::height()){
        currAgent->getPos()->setY(0);
    }
   else if (currAgent->getPos()->getY()  < 0){
        currAgent->getPos()->setY(QWidget::height());
    }

}

void
GuiFlockingArea::addObstacle(){

    m_Obstacles.push_back(std::make_shared<Obstacle>((rand()) % QWidget::width() ,
                                                     (rand()) % QWidget::height(), 0,
                                                     "obstacle", (rand() + 30) % 150));

}

void
GuiFlockingArea::removeObstacle(){

    if(m_Obstacles.size() <= 0){
        return;
    }

    m_Obstacles.pop_back();


}

void
GuiFlockingArea::paintObstacles()
{
    std::vector<std::shared_ptr<Obstacle> >::iterator it;

    for (it = m_Obstacles.begin() ; it != m_Obstacles.end(); ++it){

        Obstacle * currObstacle = it->get();


        QPen redPen(QColor(255,0,0));
        QPen blackPen(QColor(0,0,0));
        QBrush redBrush(QColor(255,0,0));
        QBrush blackBrush(QColor(0,0,0));

        QPainter painter(this);
        painter.setBrush(redBrush);
        painter.setPen(redPen);
        painter.drawEllipse(currObstacle->getX(), currObstacle->getY(), currObstacle->getRadius(), currObstacle->getRadius());
        painter.save();
        painter.restore();



        // Some misc. drawing commands for the drawing area
        painter.setRenderHint(QPainter::Antialiasing, false);
    }

}

void
GuiFlockingArea::paintPredators()
{


    // Create a prey agent with center at origin
    const QPoint preyPoints[4] = {
        QPoint(-5, -7),
        QPoint( 5, -7),
        QPoint( 0,  7),
        QPoint(-5, -7)
    };

    QPen redPen(QColor(255,0,0));
    QPen blackPen(QColor(0,0,0));
    QBrush redBrush(QColor(255,0,0));
    QBrush blackBrush(QColor(0,0,0));

    QPainter painter(this);
    painter.setBrush(brush);

    // Draw one agent's triangle
    // The values in the translate and rotate should come from
    // each agent's instance.  In other words, you'll call these
    // next few lines in a loop over all agents.

    std::vector<std::shared_ptr<Agent> >::iterator it;

    for (it = m_Predators.begin() ; it != m_Predators.end(); ++it){


        // Get current prey from shared pointer and assigned to currAgent
        Agent * currAgent = it->get();

        //apply behaviors
        wrapAround(currAgent);
        updateAgentPosition(currAgent);

        painter.save();
        //currAgent->testing();
        painter.translate(currAgent->getPos()->getX(), currAgent->getPos()->getY());
        painter.rotate(currAgent->getHeading());
        painter.setPen(redPen);
        painter.setBrush(redBrush);
        painter.drawPolygon(preyPoints, 4);
        painter.restore();



        // Some misc. drawing commands for the drawing area
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
    }
}

void
GuiFlockingArea::aheadVectorSwitch(){

    m_AheadVector =  !m_AheadVector;

}

void
GuiFlockingArea::changeAvoid(float avoid){

    m_Avoid = avoid;

}

void
GuiFlockingArea::changeAlign(float align){

    m_Align = align;
}

void
GuiFlockingArea::changeApproach(float approach){

    m_Approach = approach;

}






