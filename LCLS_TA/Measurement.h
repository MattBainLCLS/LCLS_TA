#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

class Measurement : public QWidget
{
	Q_OBJECT

private:

	QLabel* panelTitle;
	
	QVBoxLayout* measurementLayout;

	QHBoxLayout* runLayout;
	QPushButton* runButton;
	QPushButton* stopButton;

	QPushButton* generateDelays;

	bool running;

	void toggleRun();

public:

	Measurement(QWidget* parent = nullptr);
	~Measurement();

	bool isRunning();
};

