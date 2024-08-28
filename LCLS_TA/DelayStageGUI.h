#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "DelayStage.h"

class DelayStageGUI : public QWidget
{
	Q_OBJECT
private:

	DelayStage* delayStage;

	double position;
	double jogSize;

	QLabel* panelTitle;

	QHBoxLayout* jogLayout;
	QPushButton* jogLeftButton;
	QLineEdit* jogSizeText;
	QLabel* jogUnitsLabel;
	QPushButton* jogRightButton;
	
	QHBoxLayout* posLayout;
	QLabel* posLabel;
	QLabel* posValue;
	QLabel* posUnit;

	QPushButton* setTimeZeroButton;

	QVBoxLayout* delayStageLayout;

	// Motion functions

	void jogRight();
	void jogLeft();
	void updatejogSize();

	void setTimeZero();

public:
	DelayStageGUI(QWidget* parent = nullptr);
	~DelayStageGUI();

	double getPosition();

	QVBoxLayout* getLayout();

	
};

