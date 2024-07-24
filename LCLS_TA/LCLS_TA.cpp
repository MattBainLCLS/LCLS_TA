#include "LCLS_TA.h"

LCLS_TA::LCLS_TA(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QVBoxLayout* liveGraphLayout = new QVBoxLayout(parent);
    QHBoxLayout* liveGraphButtonLayout = new QHBoxLayout(parent);


    // liveGraph
    liveGraph = new QChart();
    series = new QLineSeries(this);

    for (int i = 0; i < 100; i++)
    {
        series->append(i, 0);
    }

    liveGraph->legend()->hide();
    liveGraph->addSeries(series);
    liveGraph->createDefaultAxes();
    liveGraphVerticalAxis = liveGraph->axes(Qt::Vertical);
    liveGraphVerticalAxis.first()->setRange(0, 1);
    liveGraphHorizontalAxis = liveGraph->axes(Qt::Horizontal);
    liveGraphHorizontalAxis.first()->setRange(0, 100);
    liveGraph->setVisible(true);

    QChartView* liveGraphView = new QChartView(liveGraph, this);
    liveGraphView->setRenderHints(QPainter::Antialiasing);
    liveGraphView->setVisible(true);


    //Buttons
    grabButton = new QPushButton("Grab", this);
    connect(grabButton, &QPushButton::released, this, &LCLS_TA::randomize);

    saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::released, this, &LCLS_TA::save);


    liveGraphLayout->addWidget(liveGraphView);
    
    liveGraphButtonLayout->addWidget(grabButton);
    liveGraphButtonLayout->addWidget(saveButton);

    liveGraphLayout->addLayout(liveGraphButtonLayout);

    QWidget* liveWindow = new QWidget();
    liveWindow->setLayout(liveGraphLayout);
    setCentralWidget(liveWindow);

    
}

void LCLS_TA::randomize()
{
    
    for (int i = 0; i < 100; i++) // Should replace with  for (auto& x: series) //{*/ modify x*/}
    {
        series->replace(i, i, ((double)rand() / (RAND_MAX)));
    }


}

void LCLS_TA::save()
{

    QString file_name = QFileDialog::getSaveFileName(this,
        "Select File",
        "C:\\Users\\mattbain-a\\Documents\\");
   
    std::ofstream my_file;
    my_file.open(file_name.toStdString().c_str());
    
    for (auto point : series->points())
    {
        my_file << point.x() << "," << point.y() << std::endl;
    }

    my_file.close();

}

LCLS_TA::~LCLS_TA()
{
    delete liveGraph;
}
