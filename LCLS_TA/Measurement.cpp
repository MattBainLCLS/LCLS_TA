#include "Measurement.h"

Measurement::Measurement(QWidget* parent) : QWidget(parent)
{
	running = false;

	panelTitle = new QLabel(this);

	panelTitle->setText("Transient Absorption");
	panelTitle->setAlignment(Qt::AlignCenter);
	panelTitle->setStyleSheet("border-bottom-width: 1px; border-bottom-style: solid; border-radius: 0px; font: 18pt;");

	measurementLayout = new QVBoxLayout(this);

	runLayout = new QHBoxLayout();
	runButton = new QPushButton(this);
	stopButton = new QPushButton(this);
	generateDelays = new QPushButton(this);

	runButton->setText("Run");
	runButton->setStyleSheet("color: green");
	connect(runButton, &QPushButton::released, this, &Measurement::toggleRun);

	stopButton->setText("Stop");
	stopButton->setStyleSheet("color: red");

	generateDelays->setText("Generate Delays");
	connect(generateDelays, &QPushButton::released, this, &Measurement::showDelayGenerator);

	runLayout->addWidget(runButton);
	runLayout->addWidget(stopButton);

	measurementLayout->addWidget(panelTitle);
	measurementLayout->addLayout(runLayout);
	measurementLayout->addWidget(generateDelays);


	//
	
}

bool Measurement::isRunning()
{
	return running;
}

void Measurement::toggleRun()
{
	if (!isRunning())
	{
		runButton->setText("Pause");
		runButton->setStyleSheet("color: orange");
	}
	else
	{
		runButton->setText("Run");
		runButton->setStyleSheet("color: green");
	}
	running = !running;
}

void Measurement::showDelayGenerator()
{
	delaywindow = new DelayGenerate(nullptr, &timeDelays);
	//delaywindow->setBaseSize(1000, 750);
	delaywindow->show();
}

Measurement::~Measurement()
{

}