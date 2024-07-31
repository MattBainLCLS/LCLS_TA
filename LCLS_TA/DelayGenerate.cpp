#include "DelayGenerate.h"

//DELETE
#include <iostream>
//DELETE


DelayGenerate::DelayGenerate(QWidget* parent, std::vector<double> *timeDelayPtr) : QWidget(parent)
{

	delayPtr = timeDelayPtr;

	// Set up Window
	windowLabel = new QLabel();
	windowLabel->setText("Delay Generation");
	windowLabel->setStyleSheet("border-bottom-width: 1px; border-bottom-style: solid; border-radius: 0px; font: 18pt;");

	this->resize(1000, 750);

	// Set up Table entry
	reduceRowsButton = new QPushButton;
	increaseRowsButton = new QPushButton;
	generateDelayTableButton = new QPushButton;

	reduceRowsButton->setText("-");
	increaseRowsButton->setText("+");
	generateDelayTableButton->setText("Generate");

	connect(reduceRowsButton, &QPushButton::released, this, &DelayGenerate::onReduceRowsButton);
	connect(increaseRowsButton, &QPushButton::released, this, &DelayGenerate::onIncreaseRowsButton);
	connect(generateDelayTableButton, &QPushButton::released, this, &DelayGenerate::generateFromCells);


	delayTable = new QTableWidget();

	rowCount = 0;

	delayTable->setColumnCount(4);
	delayTable->setRowCount(rowCount);

	rowsLabel = new QLabel;

	for (int i = 0; i < 2; i++)
	{
		onIncreaseRowsButton();
	}

	QHBoxLayout* changeRowsLayout = new QHBoxLayout();
	changeRowsLayout->addWidget(reduceRowsButton);
	changeRowsLayout->addWidget(increaseRowsButton);

	QVBoxLayout* spaceGenerateLayout = new QVBoxLayout();
	spaceGenerateLayout->addWidget(rowsLabel);
	spaceGenerateLayout->addWidget(delayTable);
	spaceGenerateLayout->addLayout(changeRowsLayout);
	spaceGenerateLayout->addWidget(generateDelayTableButton);

	// Set up Manual Entry

	manualTextBlock = new QTextEdit();
	manualLoad = new QPushButton();
	manualSave = new QPushButton();
	manualGenerate = new QPushButton();
	
	manualLoad->setText("Load");
	manualSave->setText("Save");
	manualGenerate->setText("Generate");

	connect(manualSave, &QPushButton::released, this, &DelayGenerate::save);
	connect(manualLoad, &QPushButton::released, this, &DelayGenerate::load);
	connect(manualGenerate, &QPushButton::released, this, &DelayGenerate::generateDelayManual);

	QHBoxLayout* manualButtonLayout = new QHBoxLayout();
	manualButtonLayout->addWidget(manualLoad);
	manualButtonLayout->addWidget(manualSave);

	QVBoxLayout* manualLayout = new QVBoxLayout();

	manualLayout->addWidget(manualTextBlock);
	manualLayout->addLayout(manualButtonLayout);
	manualLayout->addWidget(manualGenerate);




	// Set up Delay View
	delayGraph = new QChart();
	delaySeries = new QScatterSeries(this);
	
	delaysAccept = new QPushButton();
	delaysCancel = new QPushButton();

	delaysAccept->setText("Apply");
	delaysCancel->setText("Cancel");
	delaysCancel->setStyleSheet("color : red;");

	connect(delaysAccept, &QPushButton::released, this, &DelayGenerate::closeAccept);
	connect(delaysCancel, &QPushButton::released, this, &DelayGenerate::closeCancel);

	QHBoxLayout* delaysAcceptLayout = new QHBoxLayout();
	delaysAcceptLayout->addWidget(delaysCancel);
	delaysAcceptLayout->addWidget(delaysAccept);

	delayGraph->legend()->hide();
	delayGraph->addSeries(delaySeries);
	delayGraph->createDefaultAxes();
	delayGraphVerticalAxis = delayGraph->axes(Qt::Vertical);
	delayGraphHorizontalAxis = delayGraph->axes(Qt::Horizontal);
	delayGraphVerticalAxis.first()->setTitleText("Time Delay / ps");
	delayGraphHorizontalAxis.first()->setTitleText("N");

	delaySeries->setVisible(true);
	delayGraph->setVisible(true);
	delayGraphView = new QChartView(delayGraph, this);

	QVBoxLayout* delaysGraphLayout = new QVBoxLayout();
	delaysGraphLayout->addWidget(delayGraphView);
	delaysGraphLayout->addLayout(delaysAcceptLayout);

	// TODO Once created use pointer to current delay object to load current delays (if they exist)

	delayGraphVerticalAxis.first()->setRange(0, 100);
	delayGraphHorizontalAxis.first()->setRange(0, 100);

	QHBoxLayout* panelLayout = new QHBoxLayout();
	panelLayout->addLayout(spaceGenerateLayout);
	panelLayout->addLayout(manualLayout);
	panelLayout->addLayout(delaysGraphLayout);

	QVBoxLayout* windowLayout = new QVBoxLayout(this);
	windowLayout->addWidget(windowLabel);
	windowLayout->addLayout(panelLayout);


}





void DelayGenerate::onIncreaseRowsButton()
{
	rowCount++;
	delayTable->setRowCount(rowCount);
	addRow();
}

void DelayGenerate::onReduceRowsButton()
{
	if (rowCount > 1)
	{
		rowCount--;
		delayTable->setRowCount(rowCount);
		removeRow();
	}

}

void DelayGenerate::addRow()
{
	startVector.push_back(new QLineEdit());
	startVector[rowCount-1]->setText("0");
	stopVector.push_back(new QLineEdit());
	stopVector[rowCount - 1]->setText("1");
	numberVector.push_back(new QLineEdit());
	numberVector[rowCount - 1]->setText("10");
	comboVector.push_back(new QComboBox);
	comboVector[rowCount - 1]->addItem("Lin");
	comboVector[rowCount - 1]->addItem("Log");
	delayTable->setCellWidget(rowCount - 1, 0, startVector[rowCount - 1]);
	delayTable->setCellWidget(rowCount - 1, 1, stopVector[rowCount - 1]);
	delayTable->setCellWidget(rowCount - 1, 2, numberVector[rowCount - 1]);
	delayTable->setCellWidget(rowCount - 1, 3, comboVector[rowCount - 1]);
}

void DelayGenerate::removeRow()
{ 
	// Use delete vec.back() to avoid memory leak
	delete startVector.back();
	startVector.pop_back();
	delete stopVector.back();
	stopVector.pop_back();
	delete numberVector.back();
	numberVector.pop_back();
	delete comboVector.back();
	comboVector.pop_back();

}

void DelayGenerate::generateDelayManual()
{
	// TODO implement error handling for string errors
	//QString text = manualTextBlock->toPlainText().simplified();
	//QStringList textlist = text.split(',');
	QStringList textlist = manualTextBlock->toPlainText().simplified().split(',');

	QList<QPointF> timeSeries;

	QPointF point;

	std::vector<double> manualTimes;

	manualTimes.clear();

	for (int i = 0; i < textlist.size(); i++)
	{
		manualTimes.push_back(textlist[i].toDouble());
	}

	updateGraph(manualTimes);

}

void DelayGenerate::load()
{
	QString file_name = QFileDialog::getOpenFileName(this, "Select File", "C:\\Users\\mattbain-a\\Documents\\");

	std::ifstream my_file;
	my_file.open(file_name.toStdString().c_str());


	std::vector<double> loadTimes;
	loadTimes.clear();
	std::string data;

	QString timeString;
	QList<QPointF> timeSeries;
	QPointF point;
	
	int i = 0;
	while (std::getline(my_file, data, ','))
	{	
		loadTimes.push_back(QString::fromStdString(data).toDouble());
	}

	updateGraph(loadTimes);

}

void DelayGenerate::save()
{
	QString file_name = QFileDialog::getSaveFileName(this,
		"Select File",
		"C:\\Users\\mattbain-a\\Documents\\");

	std::ofstream my_file;
	my_file.open(file_name.toStdString().c_str());

	for (const auto& time : delaySeries->points())
	{
		my_file << time.y() << ",";
	}

	my_file.close();
}

void DelayGenerate::generateFromCells()
{

	
	std::vector<double> times;

	for (int i = 0; i < rowCount; i++)
	{
		double start = startVector[i]->text().toDouble();
		double stop = stopVector[i]->text().toDouble();
		int number = numberVector[i]->text().toInt();

		std::vector<double> timepiece;

		if (comboVector[i]->itemText(comboVector[i]->currentIndex()) == "Lin")
		{
			timepiece = linspace(start, stop, number, true);
		}
		else if (comboVector[i]->itemText(comboVector[i]->currentIndex()) == "Log")
		{
			timepiece = logspace(start, stop, number, true);
		}

		times = addTimesUnique(times, timepiece);
		
		updateGraph(times);
	}
}

std::vector<double> DelayGenerate::linspace(double start, double stop, int number, bool include)
{
	// TODO implement catch on number < 0
	double div;

	include ? div = (double)(number -1) : div = (double)(number); // Check whether to include the last number!

	double delta = (stop - start) / div;

	std::vector<double> times;

	for (int i = 0; i < number; i++)
	{
		times.push_back(start + i * delta);
	}

	return times;
}

std::vector<double> DelayGenerate::logspace(double start, double stop, int number, bool include)
{
	double div;
	include ? div = (double)(number - 1) : div = (double)(number); // Check whether to include the last number! 

	double startlog = std::log10(start);
	double stoplog = std::log10(stop);

	double delta = (stoplog - startlog) / div;

	std::vector<double> times;

	for (int i = 0; i < number; i++)
	{
		times.push_back(std::pow(10, startlog + i * delta));
	}

	return times;
}

std::vector<double> DelayGenerate::addTimesUnique(std::vector<double> existingTimes, std::vector<double> timepiece)
{
	for (const auto& newTime : timepiece)
	{
		bool match = false;
		for (const auto& time : existingTimes)
		{
			time == newTime ? match = true : match = false;
		}
		if (!match) // If no match, add to the time bins
		{
			existingTimes.push_back(newTime);
		}
	}
	return existingTimes;
}

void DelayGenerate::updateGraph(std::vector<double> times)
{
	QList<QPointF> timeSeries;
	QPointF point;

	delayPtr->clear();

	for (int i = 0; i < times.size(); i++)
	{
		point.setX(i);
		point.setY(times[i]);
		timeSeries.push_back(point);
		delayPtr->push_back(times[i]); // Update pointer back to measurement

	}
	delaySeries->replace(timeSeries);

	double max = *std::max_element(times.begin(), times.end());
	double min = *std::min_element(times.begin(), times.end());


	delayGraphHorizontalAxis.first()->setRange(0, times.size());
	delayGraphVerticalAxis.first()->setRange(min, max);

}

void DelayGenerate::closeAccept()
{
	// Insert line to return the std::vector of times (pointer back to Measurement)
	this->close();
}

void DelayGenerate::closeCancel()
{
	this->close();
}
