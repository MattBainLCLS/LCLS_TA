#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "DelayGenerate.h";

class Measurement : public QWidget
{
	Q_OBJECT

private:

	DelayGenerate* delaywindow;

	QLabel* panelTitle;
	
	QVBoxLayout* measurementLayout;

	QHBoxLayout* runLayout;
	QPushButton* runButton;
	QPushButton* stopButton;

	QPushButton* generateDelays;

	bool running;

	void toggleRun();
	void showDelayGenerator();

public:

	Measurement(QWidget* parent = nullptr);
	~Measurement();

	bool isRunning();
};

