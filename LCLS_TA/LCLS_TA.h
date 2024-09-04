#pragma once
#include "DelayStageGUI.h"

#include <QtWidgets/QMainWindow>
#include "ui_LCLS_TA.h"
#include <fstream>

#include <QtCore>
#include <QtGui>
#include <QtCharts>

#include "camera.h"

#include "Measurement.h"
#include "LiveBuffer.h"
#include "Frame.h"

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
    QPushButton* saveRawButton;
    QTimer* liveTimer;

    QComboBox* liveGraphCombo;
    QLineEdit* bufferSizeEdit;

    QChart* liveGraph;
    QList<QAbstractAxis*> liveGraphVerticalAxis;
    QList<QAbstractAxis*> liveGraphHorizontalAxis;

    QLabel* statusBox;
    QPushButton* initializeButton;

    // Hardware
    Camera* camera;

    void randomize();

    void snap();
    void snapToBuffer();
    void save();
    void saveRaw();
    void toggleHardware();
    void toggleLive();

    LiveBuffer liveBuffer;

    void resizeBuffer();
    void rescaleYAxis();


};
