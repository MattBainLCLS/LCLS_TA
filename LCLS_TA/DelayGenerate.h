#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <QtCharts>

#include <vector>
#include <cmath>
#include <fstream>
#include <string>




class DelayGenerate : public QWidget
{
private:
	
	// Table

	QLabel* windowLabel;
	QPushButton* reduceRowsButton;
	QPushButton* increaseRowsButton;
	QPushButton* generateDelayTableButton;

	QTableWidget* delayTable;

	QLabel* rowsLabel;
	int rowCount;
	std::vector<QLineEdit*> startVector;
	std::vector<QLineEdit*> stopVector;
	std::vector<QLineEdit*> numberVector;
	std::vector<QComboBox*> comboVector;

	void onReduceRowsButton();
	void onIncreaseRowsButton();
	void addRow();
	void removeRow();

	void generateFromCells();

	std::vector<double> linspace(double start, double stop, int number, bool include);
	std::vector<double> logspace(double start, double stop, int number, bool include);
	std::vector<double> addTimesUnique(std::vector<double> times, std::vector<double> timepiece);

	

	// Manual Entry

	QTextEdit* manualTextBlock;
	QPushButton* manualSave;
	QPushButton* manualLoad;
	QPushButton* manualGenerate;

	std::vector<double> manualTimes;

	void generateDelayManual();

	void load();
	void save();
	

	// Graph

	QChart* delayGraph;
	QList<QAbstractAxis*> delayGraphVerticalAxis;
	QList<QAbstractAxis*> delayGraphHorizontalAxis;
	QScatterSeries* delaySeries;
	QChartView* delayGraphView;
	QPushButton* delaysAccept;
	QPushButton* delaysCancel;

	void closeAccept();
	void closeCancel();

	void updateGraph(std::vector<double> times);

public:
	DelayGenerate(QWidget* parent = nullptr);



};

