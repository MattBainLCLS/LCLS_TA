#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

class DelayStage : public QWidget
{
	Q_OBJECT
private:

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

	QVBoxLayout* delayStageLayout;

	// Motion functions

	void jogRight();
	void jogLeft();
	void updatejogSize();

public:
	DelayStage(QWidget* parent = nullptr);
	~DelayStage();

	double getPosition();

	QVBoxLayout* getLayout();

	
};

