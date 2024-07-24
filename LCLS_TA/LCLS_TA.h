#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LCLS_TA.h"
#include <fstream>

#include <QtCore>
#include <QtGui>
#include <QtCharts>

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
    QPushButton* saveButton;
    QChart* liveGraph;
    QList<QAbstractAxis*> liveGraphVerticalAxis;
    QList<QAbstractAxis*> liveGraphHorizontalAxis;

    QLabel* statusBox;

    void randomize();
    void save();

};
