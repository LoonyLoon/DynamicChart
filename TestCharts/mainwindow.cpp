#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList functions = {"1. f(x) = A*(x*x) + B*x + C",
                             "2. f(x) = A * sin(x) + B * cos( C*x )",
                             "3. f(x) = A*log( B*x )",
                             "4. f(x) = A / ( sin(x*x) * B )"};

    ui->BoxChangeCharts->insertItems(1, functions);

    ui->lineA->setValidator(new QRegExpValidator(QRegExp("[0-9.-]+"),this));
    ui->lineB->setValidator(new QRegExpValidator(QRegExp("[0-9.-]+"),this));
    ui->lineC->setValidator(new QRegExpValidator(QRegExp("[0-9.-]+"),this));
    ui->lineStep->setValidator(new QRegExpValidator(QRegExp("[0-9.-]+"),this));

    connect(this, SIGNAL(newOperation()), this, SLOT(init()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_timer;
    delete chart;
    delete myview;
}

void MainWindow::init()
{
    m_timer = new QTimer();
    chart = new Chart();
    myview = new MyChartView(chart);


    chart->setTitle("Dynamic spline chart");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);

    myview->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout_3->addWidget(myview, 0,0);


    connect(this, SIGNAL(changeChart(int)),
            chart, SLOT(setFunction(int)));

    connect(this, SIGNAL(showResults(int)),
            myview, SLOT(OpenWidgetResults(int)));

    connect(m_timer, SIGNAL(timeout()),
            chart, SLOT(PaintChart()));

    connect(this, SIGNAL(sendParamsABC()),
            chart, SLOT(sendParamsToTable()));

    connect(chart, SIGNAL(sendToTableParams(QVector<QString>)),
            myview, SLOT(getParams(QVector<QString>)));

    connect(this, SIGNAL(sendParametrs(qreal,qreal,qreal,qreal)),
            chart, SLOT(setParametrs(qreal,qreal,qreal,qreal)));

    connect (chart, SIGNAL(sendToTable(QVector<qreal>, QVector<qreal>)),
             myview, SLOT(getResult(QVector<qreal>, QVector<qreal>)));


    connect(myview, SIGNAL(sendLoadParams(QVector<QString>)),
            this, SLOT(getLoadParams(QVector<QString>)));

    connect(myview, SIGNAL(sendLoadXY(QVector<qreal>, QVector<qreal>)),
                           chart, SLOT(repaint(QVector<qreal>, QVector<qreal>)));

    connect(this, SIGNAL(newSendParametrs(qreal,qreal, qreal, int)),
             chart, SLOT(getNewParams(qreal,qreal,qreal, int)));



}


void MainWindow::on_BoxChangeCharts_currentIndexChanged(int index)
{
    qDebug()<<index;
    emit changeChart(index);
}


void MainWindow::on_StartButton_clicked()
{
    A = ui->lineA->text().toDouble();
    B = ui->lineB->text().toDouble();
    C = ui->lineC->text().toDouble();
    x = ui->lineStep->text().toDouble();

    switch (m_countPressBreak) {
    case 0:

            emit sendParametrs(A,B,C,x);
            emit sendParamsABC();
            m_timer->start(1000);

            ui->StartButton->setText("Progress");
            ui->BoxChangeCharts->setDisabled(true);
            ui->groupBox_2->setDisabled(true);

            emit showResults(0);
        break;
    case 1: m_countPressBreak = 0;
            ui->BoxChangeCharts->setDisabled(false);
            ui->groupBox_2->setDisabled(false);
            ui->StartButton->setText("Start");
//            emit showResults(0);
            delete m_timer;
            delete chart;
            delete myview;
            emit newOperation();
        break;
    }
}

void MainWindow::on_PauseButton_clicked()
{
    switch (m_countPressPause) {
    case 0: m_countPressPause = 1;
            m_timer->stop();
            ui->PauseButton->setText("Continue");
            emit showResults(1);

        break;
    case 1: m_countPressPause = 0;
            m_timer->start(1000);
            ui->PauseButton->setText("Pause");
            emit showResults(0);
        break;
    }
}

void MainWindow::on_BreakButton_clicked()
{
    m_timer->stop();
    ui->StartButton->setText("New");
    m_countPressBreak = 1;
    emit showResults(1);

    if (m_countPressPause == 1)
    {
       ui->PauseButton->setText("Pause");
       m_countPressPause = 0;
    }
}

void MainWindow::getLoadParams(QVector<QString> vecLoadPar)
{
    if (vecLoadPar.at(0).contains("f(x)=A*(x*x)+B*x+C"))
    {
        ui->BoxChangeCharts->setCurrentIndex(0);
    }

    if (vecLoadPar.at(0).contains("f(x)=A*sin(x)+B*cos(C*x)"))
    {
        ui->BoxChangeCharts->setCurrentIndex(1);
    }

    if (vecLoadPar.at(0).contains("f(x)=A*log(B*x)"))
    {
        ui->BoxChangeCharts->setCurrentIndex(2);
    }

    if (vecLoadPar.at(0).contains("f(x)=A/(sin(x*x)*B)"))
    {
        ui->BoxChangeCharts->setCurrentIndex(3);
    }

    ui->lineA->setText(vecLoadPar.at(1));
    ui->lineB->setText(vecLoadPar.at(1));
    ui->lineC->setText(vecLoadPar.at(1));
    ui->lineStep->setText(vecLoadPar.at(1));

    A = vecLoadPar.at(1).toDouble();
    B = vecLoadPar.at(2).toDouble();
    C = vecLoadPar.at(3).toDouble();
//    x = vecLoadPar.at(4).toDouble();


    emit newSendParametrs(A,B,C, ui->BoxChangeCharts->currentIndex());
}







