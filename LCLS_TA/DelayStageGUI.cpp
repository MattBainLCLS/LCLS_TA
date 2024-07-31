#include "DelayStageGUI.h"

DelayStageGUI::DelayStageGUI(QWidget *parent) : QWidget(parent)
{
	position = 0;
	jogSize = 0.1;

	//Label at the top
	panelTitle = new QLabel;
	panelTitle->setText("Delay");
	panelTitle->setAlignment(Qt::AlignCenter);
	panelTitle->setStyleSheet("border-bottom-width: 1px; border-bottom-style: solid; border-radius: 0px; font: 18pt;");

	jogLayout = new QHBoxLayout();

	jogLeftButton = new QPushButton(this);
	jogSizeText = new QLineEdit(this);
	jogUnitsLabel = new QLabel(this);
	jogRightButton = new QPushButton(this);

	jogLeftButton->setText("<");
	jogSizeText->setText("0.1");
	jogUnitsLabel->setText(" ps");
	jogRightButton->setText(">");

	jogLayout->addWidget(jogLeftButton);
	jogLayout->addWidget(jogSizeText);
	jogLayout->addWidget(jogUnitsLabel);
	jogLayout->addWidget(jogRightButton);

	connect(jogLeftButton, &QPushButton::released, this, &DelayStageGUI::jogLeft);
	connect(jogRightButton, &QPushButton::released, this, &DelayStageGUI::jogRight);

	connect(jogSizeText, &QLineEdit::returnPressed, this, &DelayStageGUI::updatejogSize);

	posLayout = new QHBoxLayout();

	posLabel = new QLabel(this);
	posValue = new QLabel(this);
	posUnit = new QLabel(this);

	posLabel->setText("Position: ");
	posValue->setText(QString::number(position, 'f', 4));
	posUnit->setText(" ps");

	posLabel->setStyleSheet("font: 18pt;");
	posValue->setStyleSheet("font: 18pt;");
	posUnit->setStyleSheet("font: 18pt;");

	posLabel->setAlignment(Qt::AlignHCenter);
	posValue->setAlignment(Qt::AlignHCenter);
	posUnit->setAlignment(Qt::AlignHCenter);

	posLayout->addWidget(posLabel);
	posLayout->addWidget(posValue);
	posLayout->addWidget(posUnit);
	posLayout->setAlignment(Qt::AlignCenter);

	delayStageLayout = new QVBoxLayout(this);

	delayStageLayout->addWidget(panelTitle);
	delayStageLayout->addLayout(posLayout);
	delayStageLayout->addLayout(jogLayout);

	posValue->setText(QString::number(position, 'f', 4));

	delayStage = new DelayStage();
}

double DelayStageGUI::getPosition()
{
	return delayStage->getTime();
}

QVBoxLayout* DelayStageGUI::getLayout()
{
	return delayStageLayout;
}

void DelayStageGUI::jogRight()
{
	delayStage->goToTime(delayStage->getTime() + jogSize);
	posValue->setText(QString::number(delayStage->getTime(), 'f', 4));
}

void DelayStageGUI::jogLeft()
{
	delayStage->goToTime(delayStage->getTime() - jogSize);
	posValue->setText(QString::number(delayStage->getTime(), 'f', 4));
}

void DelayStageGUI::updatejogSize()
{
	jogSize = jogSizeText->text().toDouble();
	
}

DelayStageGUI::~DelayStageGUI()
{
	delete jogLayout;
	delete jogLeftButton;
	delete jogSizeText;
	delete jogUnitsLabel;
	delete jogRightButton;
	
	delete posLayout;
	delete posLabel;
	delete posValue;
	delete posUnit;

	delete delayStageLayout;

	delete delayStage;
}