#include "Measurement.h"

#include <qdebug.h>

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
	stopButton->setEnabled(false);

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
		stopButton->setEnabled(true);
		runScan();
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

void Measurement::setDelayStage(DelayStage* newDelayStage)
{
	delayStage = newDelayStage;
}

void Measurement::setCamera(Camera* newCamera)
{
	camera = newCamera;
}

void Measurement::setBuffer(LiveBuffer* myBuffer)
{
	liveBuffer = myBuffer;
}
void Measurement::setLiveTimer(QTimer* newLiveTimer)
{
	liveTimer = newLiveTimer;;
}

void Measurement::runScan()
{
	qInfo() << "Running scan";
	//liveBuffer = new LiveBuffer(3);
	//liveTimer->start();

	std::string fileName = QFileDialog::getSaveFileName(this, "Save File", "C:\\Users\\mattbain-a\\Data").toStdString();
	//std::string savePath = "C:\\Users\\mattbain-a\\Data\\" + fileName;
	
	for (int i = 0; i < timeDelays.size(); i++)
	{
		delayStage->goToTime(timeDelays[i]);
		Frame grabbedData(camera->snap());
		//liveBuffer->update(grabbedData);
		// Placeholder for saving data
		saveData(grabbedData, timeDelays[i], fileName);
	}

	//liveTimer->stop();
}

void Measurement::saveData(Frame data, double time, std::string savePath)
{
	std::ofstream saveFile;
	//saveFile.open("C:\\Users\\mattbain-a\\Data\\dataout.csv", std::ios_base::app);
	saveFile.open(savePath, std::ios_base::app);
	arma::vec* pumpoff = data.pumpOffIntensities();
	arma::vec* pumpon = data.pumpOnIntensities();
	arma::vec* ta = data.transientAbsorptionIntensities();
	
	saveFile << time << std::endl;
	for (int i = 0; i < pumpoff->n_elem; i++)
	{
		saveFile << pumpoff->at(i) << ",";
	}
	saveFile << std::endl;
	for (int i = 0; i < pumpon->n_elem; i++)
	{
		saveFile << pumpon->at(i) << ",";
	}
	saveFile << std::endl;
	for (int i = 0; i < ta->n_elem; i++)
	{
		saveFile << ta->at(i) << ",";
	}
	saveFile << std::endl;
	saveFile.close();
}

Measurement::~Measurement()
{

}