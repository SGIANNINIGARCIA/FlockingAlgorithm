#pragma once

#include <Vector2d.h>
#include <QObject>
#include <iostream>
#include <math.h>

class Agent : public QObject
{
    Q_OBJECT

private:
    bool        m_avoidingObstacle;

protected:
    float       m_x;
    float       m_y;
    double      m_heading;
    Vector2d    m_pos;
    Vector2d    m_vel;
    Vector2d    m_acc;
    Vector2d    m_ahead;
    std::string m_type;

public:
    Agent(int x,
          int y,
          double heading,
          std::string type);
    Agent();
   ~Agent();

    void setX(float);
    void setY(float);
    void setHeading(double);
    void setType(std::string);
    float getX();
    float getY();
    double getHeading();
    std::string getType();
    void setPos(Vector2d);
    void setVel(Vector2d);
    void setAcc(Vector2d);
    void setAhead(Vector2d);
    void setAvoidingObstacle(bool);
    Vector2d* getPos();
    Vector2d getVel();
    Vector2d getAcc();
    Vector2d getAhead();
    bool getAvoidingObstacle();
    void updateAgent();


    // Your getters and setters will go here
    // ...

    //
    // You may find the following methods useful
    //
    void addToVel(Vector2d &vec);
    void addToPos(Vector2d &vec);
    void resetAcc();

    // You should randomize the starting vel for a nice initial effect
    void resetVel();
    void stop();
    void steer(Vector2d vec);
    bool isPredator();
    void testing();

public slots:


};

