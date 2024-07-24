#include "LCLS_TA.h"

LCLS_TA::LCLS_TA(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QVBoxLayout* liveGraphLayout = new QVBoxLayout(parent);

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

    grabButton = new QPushButton("Grab", this);
    connect(grabButton, &QPushButton::released, this, &LCLS_TA::randomize);

    liveGraphLayout->addWidget(liveGraphView);
    liveGraphLayout->addWidget(grabButton);

    QWidget* liveWindow = new QWidget();
    liveWindow->setLayout(liveGraphLayout);
    setCentralWidget(liveWindow);

    
}

void LCLS_TA::randomize()
{
    for (int i = 0; i < 100; i++) // Should replace with  for (auto& x: series) {*/ modify x*/}
    {
        series->replace(i, i, ((double)rand() / (RAND_MAX)));
    }
}

LCLS_TA::~LCLS_TA()
{
    delete liveGraph;
}
