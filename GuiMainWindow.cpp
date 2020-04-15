#include "GuiFlockingArea.h"
#include "GuiMainWindow.h"
#include "Constants.h"

#include <QtWidgets>
#include <QTimer>
#include <QFrame>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>
#include <QLineEdit>
#include <QToolTip>
#include <QWhatsThis>
#include <string>

#include <iostream>

GuiMainWindow::GuiMainWindow()
{
    // Create flocking area widget
    m_FlockingAreaWidget = new GuiFlockingArea(this);

    // Create animation timer and set its callback
    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(callback_timerUpdated()));
    //animationTimer->setInterval(50);
    animationTimer->start(100);

    // Create animation timer and set its callback for 50 milliseconds
    //animationTimer->setInterval(50);

    // Set the vertical layout for the flocking drawing area widget and place
    // it in a QFrame so there's a line on its border. Make the frame's minimum
    // size 200x300.
    QVBoxLayout* flockLayout = new QVBoxLayout;
    flockLayout->addWidget(m_FlockingAreaWidget);
    QFrame* frame = new QFrame;
    frame->setLayout(flockLayout);
    frame->setMinimumSize(200,300);

    // Create the main vertical layout
    QVBoxLayout* mainLayout      = new QVBoxLayout;

    // Create the control widgets under the flocking drawing area
    QSpacerItem* spacerItem       = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QLabel*      speedLBL         = new QLabel("Speed");
    QLabel*      avoidLBL         = new QLabel("Avoid");
    QLabel*      alignLBL         = new QLabel("Align");
    QLabel*      approachLBL      = new QLabel("Approach");
    QLabel*      numPreyLBL       = new QLabel("Num Prey:");
    QLabel*      numPredatorsLBL  = new QLabel("Num Predators:");
    QLabel*      numObstaclesLBL  = new QLabel("Num Obstacles:");
    QCheckBox*   lookAheadVectors = new QCheckBox("Look-Ahead Vectors", this);
                 numPrey          = new QLineEdit();
                 numPredators     = new QLineEdit();
                 numObstacles     = new QLineEdit();

    // Create the vertical layout for the speed slider and label
    QVBoxLayout* speedLayout     = new QVBoxLayout;
    QVBoxLayout* avoidLayout     = new QVBoxLayout;
    QVBoxLayout* alignLayout     = new QVBoxLayout;
    QVBoxLayout* approachLayout  = new QVBoxLayout;


    // Create the horizontal layouts for the labels & textboxes, the controls, and the buttons
    QHBoxLayout* labelsLayout    = new QHBoxLayout;
    QHBoxLayout* controlsLayout  = new QHBoxLayout;
    QHBoxLayout* buttonLayout    = new QHBoxLayout;

    // Create the control widgets
    m_RunPB                      = new QPushButton("Go");
    m_RunPB->setCheckable(true);
    m_AddPreyPB                  = new QPushButton("Add Prey");
    m_AddObstaclePB              = new QPushButton("Add Obstacle");
    m_RemoveObstaclesPB          = new QPushButton("Remove Obstacles");
    m_AddPredatorPB              = new QPushButton("Add Predators");
    m_RemovePredatorsPB          = new QPushButton("Remove Predators");
    m_ResetPB                    = new QPushButton("Reset");
    m_TestPB                     = new QPushButton("Test");

    m_SpeedSL                    = new QSlider();
    m_SpeedSL->setOrientation(Qt::Orientation::Vertical);

    m_AvoidSL                    = new QSlider();
    m_AvoidSL->setOrientation(Qt::Orientation::Vertical);

    m_AlignSL                    = new QSlider();
    m_AlignSL->setOrientation(Qt::Orientation::Vertical);

    m_ApproachSL                 = new QSlider();
    m_ApproachSL->setOrientation(Qt::Orientation::Vertical);

    // Add the frame containing the flocking area widget to the main layout
    mainLayout->addWidget(frame);
    mainLayout->setStretch(0, 1);

    // Add the labels and line edit widgets to the labels layout making sure the
    // checkbox is all the way over to the right
    labelsLayout->addWidget(numPreyLBL);
    labelsLayout->addWidget(numPrey);
    labelsLayout->addWidget(numPredatorsLBL);
    labelsLayout->addWidget(numPredators);
    labelsLayout->addWidget(numObstaclesLBL);
    labelsLayout->addWidget(numObstacles);
    labelsLayout->addSpacerItem(spacerItem);
    labelsLayout->addWidget(lookAheadVectors);

    // Add the speed widgets to the speed layout
    speedLayout->addWidget(m_SpeedSL);
    speedLayout->addWidget(speedLBL);

    avoidLayout->addWidget(m_AvoidSL);
    avoidLayout->addWidget(avoidLBL);

    alignLayout->addWidget(m_AlignSL);
    alignLayout->addWidget(alignLBL);

    approachLayout->addWidget(m_ApproachSL);
    approachLayout->addWidget(approachLBL);


    // Add the speed layout to the controls layout use spacer items to nicely
    // separate the sub-layouts (i.e., speed, separation)
    // controlsLayout->addSpacerItem(spacerItem);
    controlsLayout->addSpacerItem(spacerItem);
    controlsLayout->addLayout(speedLayout);
    controlsLayout->addSpacerItem(spacerItem);
    controlsLayout->addLayout(avoidLayout);
    controlsLayout->addSpacerItem(spacerItem);
    controlsLayout->addLayout(alignLayout);
    controlsLayout->addSpacerItem(spacerItem);
    controlsLayout->addLayout(approachLayout);
    controlsLayout->addSpacerItem(spacerItem);


    // Add the buttons to the horizontal button layout
    buttonLayout->addWidget(m_RunPB);
    buttonLayout->addWidget(m_AddPreyPB);
    buttonLayout->addWidget(m_AddObstaclePB);
    buttonLayout->addWidget(m_RemoveObstaclesPB);
    buttonLayout->addWidget(m_AddPredatorPB);
    buttonLayout->addWidget(m_RemovePredatorsPB);
    buttonLayout->addWidget(m_ResetPB);
    buttonLayout->addWidget(m_TestPB);

    // Add the sub-layouts to the main layout
    mainLayout->addLayout(labelsLayout);
    mainLayout->addLayout(controlsLayout);
    mainLayout->addLayout(buttonLayout);

    // Set the widths appropriately on the line edit widgets and set them all
    // to read only and right aligned
    numPrey->setReadOnly(true);
    numPrey->setAlignment(Qt::AlignRight);
    numPrey->setFixedWidth(40);
    numPredators->setReadOnly(true);
    numPredators->setAlignment(Qt::AlignRight);
    numPredators->setFixedWidth(40);
    numObstacles->setReadOnly(true);
    numObstacles->setAlignment(Qt::AlignRight);
    numObstacles->setFixedWidth(40);


    // Set mainLayout as the main layout
    setLayout(mainLayout);

    // Set the stretch appropriately for the 3 layout members of mainLayout

    // Create connections for the controls

    connect(m_RunPB,            SIGNAL(toggled(bool)),
            this,               SLOT(updateGoButton(bool)));

    connect(m_AddPreyPB,        SIGNAL(clicked()),
            this,               SLOT(callback_addPrey()));

    connect(m_AddObstaclePB,    SIGNAL(clicked()),
            this,               SLOT(callback_addObstacle()));

    connect(m_RemoveObstaclesPB,SIGNAL(clicked()),
            this,               SLOT(callback_removeObstacles()));

    connect(m_AddPredatorPB,    SIGNAL(clicked()),
            this,               SLOT(callback_addPredator()));

    connect(m_RemovePredatorsPB,SIGNAL(clicked()),
            this,               SLOT(callback_removePredators()));

    connect(m_ResetPB,          SIGNAL(clicked()),
            this,               SLOT(callback_reset()));

    connect(m_TestPB,           SIGNAL(clicked()),
            this,               SLOT(callback_test()));

    connect(lookAheadVectors,   SIGNAL(stateChanged(int)),
            this,               SLOT(callback_lookAheadVector(int)));



    connect(m_SpeedSL,          SIGNAL(valueChanged(int)),
            this,               SLOT(callback_speedChanged(int)));

    connect(m_AvoidSL,          SIGNAL(valueChanged(int)),
            this,               SLOT(callback_avoidChanged(int)));

    connect(m_AlignSL,          SIGNAL(valueChanged(int)),
            this,               SLOT(callback_alignChanged(int)));

    connect(m_ApproachSL,          SIGNAL(valueChanged(int)),
            this,               SLOT(callback_approachChanged(int)));


    // Set the size policy so that the flocking area stretches when the
    // main window resizes
    QSizePolicy sizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    sizePolicy.setVerticalStretch(1);
    m_FlockingAreaWidget->setSizePolicy(sizePolicy);


    // Add tool tips for all the widgets
    m_RunPB->setToolTip("Start Flocking Simulation");
    m_AddPreyPB->setToolTip("Add preys to the simulation");
    m_AddObstaclePB->setToolTip("Add an obstacle at a random position");
    m_RemoveObstaclesPB->setToolTip("Remove an obstacle");
    m_AddPredatorPB->setToolTip("Add a predator to the simulation");
    m_RemovePredatorsPB->setToolTip("Remove predator from simulation");
    m_ResetPB->setToolTip("Reset the simulation");
    m_TestPB->setToolTip("Run simulation with only one prey for testing");
    m_SpeedSL->setToolTip("Increment speed of simulation");
    m_AlignSL->setToolTip("Increment align behaviour in simulation");
    m_ApproachSL->setToolTip("Increment approach behaviour in simulation");
    m_AvoidSL->setToolTip("Increment avoidance behaviour in simulation");
    lookAheadVectors->setToolTip("Display vectors of prey");

    // Add a WhatsThis help message for at least one widget

    m_AddPreyPB->setWhatsThis("This button adds 10 more preys to the simulation");

    // Set main window title
    setWindowTitle("Flocking");

    // Set the brush style to solid for the subsequent drawing
    QBrush brush(Qt::SolidPattern);

    // create the prey agents
    m_FlockingAreaWidget->initialize();
    updateInfo();


}


void
GuiMainWindow::updateInfo(){


    //UPDATES THE QLINEEDITS
    numPrey->setText(QString::number( m_FlockingAreaWidget->getNumPrey()));
    numObstacles->setText(QString::number( m_FlockingAreaWidget->getNumObstacles()));
    numPredators->setText(QString::number( m_FlockingAreaWidget->getNumPredators()));

}

void
GuiMainWindow::callback_speedChanged(int value)
{
    std::cout << "Speed changed to: " << value << std::endl;
    animationTimer->setInterval(100 - value);



}

void
GuiMainWindow::callback_avoidChanged(int value)
{
    std::cout << "Avoid changed to: " << value << std::endl;
    m_FlockingAreaWidget->changeAvoid(((float)value / 10) + 0.1);

}

void
GuiMainWindow::callback_alignChanged(int value)
{
    std::cout << "Align changed to: " << value << std::endl;
    m_FlockingAreaWidget->changeAlign(((float)value / 10) + 0.1);
}

void
GuiMainWindow::callback_approachChanged(int value)
{
    std::cout << "Approach changed to: " << value << std::endl;
    m_FlockingAreaWidget->changeApproach(((float)value / 10) + 0.1);
}

void
GuiMainWindow::callback_run()
{
   std::cout << "Run button hit" << std::endl;
   updateGoButton(m_RunPB->isChecked());

}

void
GuiMainWindow::callback_test()
{
   std::cout << "test button hit" << std::endl;
}

void
GuiMainWindow::callback_addPrey()
{
   std::cout << "Add Prey button hit" << std::endl;
   m_FlockingAreaWidget->addPrey();

   //Update GUI
   updateInfo();



}

void
GuiMainWindow::callback_addObstacle()
{
   std::cout << "add Obstacle button hit" << std::endl;
   m_FlockingAreaWidget->addObstacle();

   //Update GUI
   updateInfo();

}

void
GuiMainWindow::callback_lookAheadVector(int check)
{
    if(check == 2){
        std::cout << "Look-ahead vector checked" << std::endl;
    } else {
        std::cout << "Look-ahead vector unchecked" << std::endl;
    }

    m_FlockingAreaWidget->aheadVectorSwitch();

}

void
GuiMainWindow::updateGoButton(bool status)
{
    m_FlockingAreaWidget->changeStatus();

    if (status) {
        m_RunPB->setText("Stop");
    } else {
        m_RunPB->setText("Go");
    }
}

void
GuiMainWindow::callback_removeObstacles()
{
   std::cout << "remove Obstacle button hit" << std::endl;
   m_FlockingAreaWidget->removeObstacle();

   //Update GUI
   updateInfo();



}

void
GuiMainWindow::callback_addPredator()
{
   std::cout << "add predator button hit" << std::endl;

   m_FlockingAreaWidget->addPredator();

   //Update GUI
   updateInfo();

}

void
GuiMainWindow::callback_removePredators()
{
   std::cout << "remove predator button hit" << std::endl;

   m_FlockingAreaWidget->removePredator();

   //Update GUI
   updateInfo();

}

void
GuiMainWindow::callback_reset()
{
   std::cout << "reset button hit" << std::endl;
   m_FlockingAreaWidget->initialize();

   //update GUI
   updateInfo();

}

void
GuiMainWindow::callback_enableWhatsThis() {
    QWhatsThis::enterWhatsThisMode();
}

void
GuiMainWindow::callback_timerUpdated(){
     m_FlockingAreaWidget->update();
}

