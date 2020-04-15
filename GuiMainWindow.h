#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <memory>

class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSlider;
class QSpinBox;
class QHBoxLayout;
class QVBoxLayout;
class GuiFlockingArea;

class GuiMainWindow : public QWidget
{
    Q_OBJECT

private:
    GuiFlockingArea* m_FlockingAreaWidget;
    QPushButton*     m_RunPB;
    QPushButton*     m_TestPB;
    QPushButton*     m_AddPreyPB;
    QPushButton*     m_AddObstaclePB;
    QPushButton*     m_RemoveObstaclesPB;
    QPushButton*     m_AddPredatorPB;
    QPushButton*     m_RemovePredatorsPB;
    QPushButton*     m_ResetPB;
    QTimer*          animationTimer;
    QSlider*         m_SpeedSL;
    QSlider*         m_AvoidSL;
    QSlider*         m_AlignSL;
    QSlider*         m_ApproachSL;
    QCheckBox*       lookAheadVectors;
    QLineEdit*       numPrey;
    QLineEdit*       numPredators;
    QLineEdit*       numObstacles;


    void updatePreyLE(int numPrey);
    void updatePredatorsLE(int numPredators);
    void updateObstaclesLE(int numObstacles);
    void removeAll();
    void callback_numPreyTextEdit();
    void updateInfo();



public:
    GuiMainWindow();
   ~GuiMainWindow() {
    }

private slots:
    void callback_run();
    void callback_speedChanged(int value);
    void callback_avoidChanged(int value);
    void callback_alignChanged(int value);
    void callback_approachChanged(int value);
    void callback_test();
    void callback_addPrey();
    void callback_addObstacle();
    void callback_removeObstacles();
    void callback_addPredator();
    void callback_removePredators();
    void callback_reset();
    void updateGoButton(bool);
    void callback_lookAheadVector(int);
    void callback_enableWhatsThis();
    void callback_timerUpdated();




};

#endif // MAINWINDOW_H
