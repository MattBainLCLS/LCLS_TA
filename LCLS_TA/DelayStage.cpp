#include "DelayStage.h"

DelayStage::DelayStage(QWidget *parent) : QWidget(parent)
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

	connect(jogLeftButton, &QPushButton::released, this, &DelayStage::jogLeft);
	connect(jogRightButton, &QPushButton::released, this, &DelayStage::jogRight);

	connect(jogSizeText, &QLineEdit::returnPressed, this, &DelayStage::updatejogSize);

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