#include "LCLS_TA.h"

#include "SapClassBasic.h"

LCLS_TA::LCLS_TA(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->resize(1600, 1000);

    QVBoxLayout* liveGraphLayout = new QVBoxLayout(parent);
    QHBoxLayout* liveGraphButtonLayout = new QHBoxLayout(parent);
    QHBoxLayout* statusLayout = new QHBoxLayout(parent);

    // Camera Status Light


    // liveGraph
    liveGraph = new QChart();
    series = new QLineSeries(this);

    liveTimer = new QTimer(this);
    connect(liveTimer, &QTimer::timeout, this, &LCLS_TA::snap);

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
    liveGraphHorizontalAxis.first()->setRange(0, 8192);
    liveGraph->setVisible(true);

    QChartView* liveGraphView = new QChartView(liveGraph, this);
    liveGraphView->setRenderHints(QPainter::Antialiasing);
    liveGraphView->setVisible(true);


    //Buttons

    liveButton = new QPushButton("Run", this);
    connect(liveButton, &QPushButton::released, this, &LCLS_TA::toggleLive);

    grabButton = new QPushButton("Grab", this);
    connect(grabButton, &QPushButton::released, this, &LCLS_TA::snap);

    saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::released, this, &LCLS_TA::save);

    initializeButton = new QPushButton("Initialize", this);
    connect(initializeButton, &QPushButton::released, this, &LCLS_TA::toggleHardware);


    //
    DelayStageGUI* mystage = new DelayStageGUI(this);
    Measurement* tacontrol = new Measurement(this);
   

    QHBoxLayout* mainLayout = new QHBoxLayout;

    // Status box
    statusBox = new QLabel(this);
    statusBox->setFrameStyle(QFrame::Box);
   

    // Build Window

    liveGraphLayout->addWidget(liveGraphView);
    liveGraphButtonLayout->addWidget(liveButton);
    liveGraphButtonLayout->addWidget(grabButton);
    liveGraphButtonLayout->addWidget(saveButton);
    
    statusLayout->addWidget(statusBox);
    statusLayout->addWidget(initializeButton);

    //// TESTING
    //DelayStage* testDelayStage = new DelayStage();


    liveGraphLayout->addLayout(liveGraphButtonLayout);
    liveGraphLayout->addLayout(statusLayout);
    //liveGraphLayout->addLayout(mystage->getLayout());
    //liveGraphLayout->addWidget(mystage);

    QVBoxLayout* controlLayout = new QVBoxLayout(parent);

    controlLayout->addWidget(mystage);
    controlLayout->addWidget(tacontrol);

    mainLayout->addLayout(liveGraphLayout, 2);
    mainLayout->addLayout(controlLayout, 1);



    QWidget* liveWindow = new QWidget();
    liveWindow->setLayout(mainLayout);
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
    //arma::Mat<double> mydata = camera->snap();
    Frame grabbedData = Frame(camera->snap());
    statusBox->setText("Spectrum size: " + QString::number(grabbedData.pumpOffIntensities()->n_elem));

    //statusBox->setText("n cols = " + QString::number(mydata.n_cols) + " n rows = " + QString::number(mydata.n_rows));

    /*QString mystr = "";
    for (int i = 40; i < grabbedData.pumpOffIndices.n_elem; i++)
    {
        mystr = mystr + QString::number(grabbedData.pumpOffIndices(i)) + ",";
    }
    
    statusBox->setText(mystr);
    */
    //camera->snap();
    
    //arma::mat mygrab = camera->snap();

    //statusBox->setText("From Frame: n cols = " + QString::number(grabbedData.test.n_cols) + " n rows = " + QString::number(grabbedData.test.n_rows));
    //;

    //QList<QPointF> mylist;



    //statusBox->setText("Snapped, updating plot");

    ////parent->updatesEnabled(false);

    //arma::vec* pumpOffData = grabbedData.pumpOffIntensities();
    //QPointF point;
    //for (int i = 0; i < pumpOffData->n_cols; i++)
    //{
    //    point.setX(i);
    //    //point.setY(data[i]);
    //    point.setY(pumpOffData->at(i));
    //    //for (int j = 0; j < 100; j++)
    //    //{
    //    //    point.setY(pumpoffdata->
    //    //    //point.setY(point.y() + data[i + 8192 * j]); // sum over the other axis
    //    //}
    //    //point.setY(point.y() / 100);
    //    
    //    mylist.push_back(point);
    //    
    //}
    //series->replace(mylist);
    
    
    //series->replace();

    //statusBox->setText("Snapped finished");
}

void LCLS_TA::toggleLive()
{
    if (!liveTimer->isActive())
    {
        liveTimer->start(100); // Start at 10 Hz
        statusBox->setText("Running");
        liveButton->setText("Stop");
        liveButton->setStyleSheet("color: red");
    }
    else
    {
        liveTimer->stop();
        statusBox->setText("Stopped");
        liveButton->setText("Run");
        liveButton->setStyleSheet("color: black");
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
