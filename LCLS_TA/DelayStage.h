#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

class DelayStage : public QWidget
{

private:
	double position;
	double jogSize;

	QHBoxLayout* jogLayout;
	QPushButton* jogLeftButton;
	QLineEdit* jogSizeText;
	QLabel* jogUnitsLabel;
	QPushButton* jogRightButton;
	
	QHBoxLayout* posLayout;
	QLabel* posLabel;
	QLabel* posValue;
	QLabel* posUnit;

	QVBoxLayout* delayStageLayout;

	// Motion functions

	void jogRight();
	void jogLeft();
	void updatejogSize();

public:
	DelayStage();
	~DelayStage();

	double getPosition();

	QVBoxLayout* getLayout();

	
};

