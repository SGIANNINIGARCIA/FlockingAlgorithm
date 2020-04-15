#ifndef FLOCKINGAREA_H
#define FLOCKINGAREA_H

#include <cmath>
#include <memory>

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <vector>
#include "Agent.h"
#include "Behaviors.h"


class GuiFlockingArea : public QWidget
{
    Q_OBJECT

    bool   m_stop = false;
    int    m_numPrey;
    int    x;
    float  m_Avoid;
    float  m_Align;
    float  m_Approach;
    bool   m_AheadVector;

    std::vector<std::shared_ptr<Agent> >    m_PreyAgents;
    std::vector<std::shared_ptr<Obstacle> > m_Obstacles;
    std::vector<std::shared_ptr<Agent> >    m_Predators;

    Behaviors behaviors;

private:
    QPen pen;
    QBrush brush;

    void updateAgentPosition(Agent * currAgent);
    void wrapAround(Agent * currAgent);
    void paintObstacles();
    void paintPredators();

public:
    GuiFlockingArea(QWidget *parent = nullptr);
   ~GuiFlockingArea(){}

    void initialize();
    void setBrush(const QBrush &brush);
    void changeStatus();
    double getNumPrey();
    void addPrey();
    void addObstacle();
    void removeObstacle();
    int getNumObstacles();
    void addPredator();
    void removePredator();
    int getNumPredators();
    void changeAvoid(float);
    void changeAlign(float);
    void changeApproach(float);
    void aheadVectorSwitch();

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif
