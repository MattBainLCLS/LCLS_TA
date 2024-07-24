#include "LCLS_TA.h"

#include "SapClassBasic.h"

LCLS_TA::LCLS_TA(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QVBoxLayout* liveGraphLayout = new QVBoxLayout(parent);
    QHBoxLayout* liveGraphButtonLayout = new QHBoxLayout(parent);
    QHBoxLayout* statusLayout = new QHBoxLayout(parent);

    // Camera Status Light


    // liveGraph
    liveGraph = new QChart();
    series = new QLineSeries(this);

    for (int i = 0; i < 8192; i++)
    {
        series->append(i, 0);
    }

    liveGraph->legend()->hide();
    liveGraph->addSeries(series);
    liveGraph->createDefaultAxes();
    liveGraphVerticalAxis = liveGraph->axes(Qt::Vertical);
    liveGraphVerticalAxis.first()->setRange(0, 4096);
    liveGraphHorizontalAxis = liveGraph->axes(Qt::Horizontal);
    liveGraphHorizontalAxis.first()->setRange(0, 100);
    liveGraph->setVisible(true);

    QChartView* liveGraphView = new QChartView(liveGraph, this);
    liveGraphView->setRenderHints(QPainter::Antialiasing);
    liveGraphView->setVisible(true);


    //Buttons
    grabButton = new QPushButton("Grab", this);
    //connect(grabButton, &QPushButton::released, this, &LCLS_TA::randomize);
    connect(grabButton, &QPushButton::released, this, &LCLS_TA::snap);

    saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::released, this, &LCLS_TA::save);

    initializeButton = new QPushButton("Initialize", this);
    connect(initializeButton, &QPushButton::released, this, &LCLS_TA::toggleHardware);


   

    

    // Status box
    statusBox = new QLabel(this);
    statusBox->setFrameStyle(QFrame::Box);
   

    // Build Window

    liveGraphLayout->addWidget(liveGraphView);

    liveGraphButtonLayout->addWidget(grabButton);
    liveGraphButtonLayout->addWidget(saveButton);
    
    statusLayout->addWidget(statusBox);
    statusLayout->addWidget(initializeButton);



    liveGraphLayout->addLayout(liveGraphButtonLayout);
    liveGraphLayout->addLayout(statusLayout);

    QWidget* liveWindow = new QWidget();
    liveWindow->setLayout(liveGraphLayout);
    setCentralWidget(liveWindow);

    camera = new Camera();
    
    statusBox->setText("Ready");
}

void LCLS_TA::randomize()
{
    
    for (int i = 0; i < 100; i++) // Should replace with  for (auto& x: series) //{*/ modify x*/}
    {
        series->replace(i, i, ((double)rand() / (RAND_MAX)));
    }

    statusBox->setText("Grabbed.");


}

void LCLS_TA::snap()
{
    statusBox->setText("Snapping..");
    
    uint16_t* data = camera->snap();

    QList<QPointF> mylist;

    statusBox->setText("Snapped, updating plot");

    //parent->updatesEnabled(false);

    QPointF point;
    for (int i = 0; i < 8192; i++)
    {
        point.setX(i);
        point.setY(data[i]);
        mylist.push_back(point);
        
    }
    series->replace(mylist);
    //series->replace();

    statusBox->setText("Snapped finished");
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

void LCLS_TA::toggleHardware()
{
    
    statusBox->setText("Initializing Camera...");
    
    if (!camera->isInitialized())
    {
        if (!camera->initialize())
        {
            statusBox->setText("Camera Initialization Failed.");
        }
        else
        {
            statusBox->setText("Initialized.");
        }
    }
    else
    {
        camera->terminate();
        statusBox->setText("Terminated.");
    }
    
}

LCLS_TA::~LCLS_TA()
{
    delete liveGraph;
}
