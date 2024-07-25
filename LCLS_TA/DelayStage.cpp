#include "DelayStage.h"

DelayStage::DelayStage()
{
	position = 0;
	jogSize = 0.1;

	jogLayout = new QHBoxLayout();

	jogLeftButton = new QPushButton("<");
	jogSizeText = new QLineEdit("0.1");
	jogUnitsLabel = new QLabel(" ps");
	jogRightButton = new QPushButton(">");

	jogLayout->addWidget(jogLeftButton);
	jogLayout->addWidget(jogSizeText);
	jogLayout->addWidget(jogUnitsLabel);
	jogLayout->addWidget(jogRightButton);

	connect(jogLeftButton, &QPushButton::released, this, &DelayStage::jogLeft);
	connect(jogRightButton, &QPushButton::released, this, &DelayStage::jogRight);

	connect(jogSizeText, &QLineEdit::returnPressed, this, &DelayStage::updatejogSize);

	posLayout = new QHBoxLayout();

	posLabel = new QLabel("Position: ");
	posValue = new QLabel(QString::number(position, 'f', 4));
	posUnit = new QLabel(" ps");

	posLayout->addWidget(posLabel);
	posLayout->addWidget(posValue);
	posLayout->addWidget(posUnit);

	delayStageLayout = new QVBoxLayout();

	delayStageLayout->addLayout(posLayout);
	delayStageLayout->addLayout(jogLayout);

	posValue->setText(QString::number(position, 'f', 4));
}

double DelayStage::getPosition()
{
	return position;
}

QVBoxLayout* DelayStage::getLayout()
{
	return delayStageLayout;
}

void DelayStage::jogRight()
{
	position = position + jogSize;
	posValue->setText(QString::number(position, 'f', 4));
}

void DelayStage::jogLeft()
{
	position = position - jogSize;
	posValue->setText(QString::number(position, 'f', 4));
}

void DelayStage::updatejogSize()
{
	jogSize = jogSizeText->text().toDouble();
	
}

DelayStage::~DelayStage()
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
}