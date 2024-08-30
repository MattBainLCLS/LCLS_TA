#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "DelayStage.h"

class DelayStageGUI : public QWidget
{
	Q_OBJECT
private:

	//Hardware
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

	DelayStage* getDelayStagePtr()
	{
		return delayStage;
	}
	~DelayStageGUI();

	double getPosition();

	QVBoxLayout* getLayout();

	
};

