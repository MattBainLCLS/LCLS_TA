#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "DelayGenerate.h"
#include "DelayStage.h"
#include "Camera.h"
#include "LiveBuffer.h"
#include "Frame.h"

#include <fstream>

class Measurement : public QWidget
{
	Q_OBJECT

private:

	// Hardware
	DelayStage* delayStage;
	Camera* camera;
	LiveBuffer* liveBuffer;
	QTimer* liveTimer;


	DelayGenerate* delaywindow;

	QLabel* panelTitle;
	
	QVBoxLayout* measurementLayout;

	QHBoxLayout* runLayout;
	QPushButton* runButton;
	QPushButton* stopButton;

	QPushButton* generateDelays;

	bool running;

	std::vector<double> timeDelays;

	void toggleRun();
	void showDelayGenerator();
	void runScan();

public:

	Measurement(QWidget* parent = nullptr);

	void setDelayStage(DelayStage* newDelayStage);
	void setCamera(Camera* newCamera);
	void setBuffer(LiveBuffer* myBuffer);
	void setLiveTimer(QTimer* newLiveTimer);

	void saveData(Frame data, double time);

	~Measurement();

	bool isRunning();
};

