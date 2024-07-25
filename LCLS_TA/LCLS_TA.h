#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LCLS_TA.h"
#include <fstream>

#include <QtCore>
#include <QtGui>
#include <QtCharts>

#include "camera.h"
#include "DelayStage.h"

class LCLS_TA : public QMainWindow
{
    Q_OBJECT

public:
    LCLS_TA(QWidget *parent = nullptr);
    ~LCLS_TA();

private:
    Ui::LCLS_TAClass ui;

    // Live visualizer variables
    QLineSeries* series;
    QPushButton* grabButton;
    QPushButton* liveButton;
    QPushButton* saveButton;
    QTimer* liveTimer;

    QChart* liveGraph;
    QList<QAbstractAxis*> liveGraphVerticalAxis;
    QList<QAbstractAxis*> liveGraphHorizontalAxis;

    QLabel* statusBox;
    QPushButton* initializeButton;

    // Hardware
    Camera* camera;

    void randomize();

    void snap();
    void save();
    void toggleHardware();
    void toggleLive();

};
