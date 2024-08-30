#include "LCLS_TA.h"

#include "SapClassBasic.h"

LCLS_TA::LCLS_TA(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    this->resize(1600, 1000);

    QVBoxLayout* liveGraphLayout = new QVBoxLayout(parent);
    QHBoxLayout* liveGraphOptionsLayout = new QHBoxLayout(parent);
    QHBoxLayout* liveGraphButtonLayout = new QHBoxLayout(parent);
    QHBoxLayout* statusLayout = new QHBoxLayout(parent);

    // Camera Status Light


    // liveGraph
    liveGraph = new QChart();
    series = new QLineSeries(this);

    liveTimer = new QTimer(this);
    connect(liveTimer, &QTimer::timeout, this, &LCLS_TA::snapToBuffer);

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
    liveButton->setEnabled(false);
    connect(liveButton, &QPushButton::released, this, &LCLS_TA::toggleLive);

    grabButton = new QPushButton("Grab", this);
    grabButton->setEnabled(false);
    connect(grabButton, &QPushButton::released, this, &LCLS_TA::snap);

    saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::released, this, &LCLS_TA::save);

    initializeButton = new QPushButton("Initialize", this);
    connect(initializeButton, &QPushButton::released, this, &LCLS_TA::toggleHardware);

    liveGraphCombo = new QComboBox(this);
    liveGraphCombo->addItem("Transient Absorption");
    liveGraphCombo->addItem("Pump Off");
    liveGraphCombo->addItem("Pump On");
    connect(liveGraphCombo, &QComboBox::currentIndexChanged, this, &LCLS_TA::rescaleYAxis);

    //bufferSize
    QLabel* bufferSizeLabel = new QLabel("Buffer Size:", this);

    QIntValidator* bufferSizeValidator = new QIntValidator();
    bufferSizeValidator->setBottom(1);
    bufferSizeEdit = new QLineEdit("3", this);
    bufferSizeEdit->setValidator(bufferSizeValidator);
    connect(bufferSizeEdit, &QLineEdit::editingFinished, this, &LCLS_TA::resizeBuffer);

    liveGraphOptionsLayout->addWidget(liveGraphCombo);
    liveGraphOptionsLayout->addWidget(bufferSizeLabel);
    liveGraphOptionsLayout->addWidget(bufferSizeEdit);


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

    liveGraphLayout->addLayout(liveGraphOptionsLayout);
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
    liveBuffer = LiveBuffer(3);


    tacontrol->setDelayStage(mystage->getDelayStagePtr());
    tacontrol->setCamera(camera);
    tacontrol->setLiveTimer(liveTimer);
    tacontrol->setBuffer(&liveBuffer);
    
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
    //LiveBuffer myBuffer = LiveBuffer(3);
    //statusBox->setText("Snapping..");

    Frame grabbedData(camera->snap());


    QList<QPointF> myList;
    QPointF point;

    arma::vec* pumpOffData = grabbedData.transientAbsorptionIntensities();

    statusBox->setText("Ta length nelem = " + QString::number(pumpOffData->n_elem));
    for (int i = 0; i < pumpOffData->n_elem; i++)
    {
        point.setX(i);
        point.setY(pumpOffData->at(i));
        myList.push_back(point);

    }

    series->replace(myList);

    //series->replace(myBuffer.getPumpOff());
    
    //series->replace(myBuffer.getTA());
    //statusBox->setText("Snapped finished");
}

void LCLS_TA::snapToBuffer()
{
    Frame grabbedData = Frame(camera->snap());
    liveBuffer.update(grabbedData);

    series->replace(liveBuffer.getTA());
}

void LCLS_TA::toggleLive()
{
    if (!liveTimer->isActive())
    {
        liveBuffer = LiveBuffer(3); // Create a fresh buffer
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
            grabButton->setEnabled(true);
            liveButton->setEnabled(true);
            statusBox->setText("Initialized.");
            
        }
    }
    else
    {
        camera->terminate();
        grabButton->setEnabled(false);
        liveButton->setEnabled(false);
        statusBox->setText("Terminated.");
    }
    
}

void LCLS_TA::resizeBuffer()
{
    liveBuffer = LiveBuffer(bufferSizeEdit->text().toInt());
    //(bufferSizeEdit->text()))
}

void LCLS_TA::rescaleYAxis()
{
    //QString graphChoice = liveGraphCombo->currentText();
    std::string graphChoiceStr = liveGraphCombo->currentText().toStdString();
    if (graphChoiceStr == "Transient Absorption")
    {
        liveGraphVerticalAxis.first()->setRange(-1E-1, 1E-1);
    }
    else
    {
        liveGraphVerticalAxis.first()->setRange(-10, 4100);
    }
}

LCLS_TA::~LCLS_TA()
{
    delete liveGraph;
}
