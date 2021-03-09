#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"
#include "mychartview.h"


#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtMath>
#include <QTimer>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void init();

signals:
    void changeChart(int);
    void showResults(int);
    void newOperation();
    void sendParametrs(qreal, qreal, qreal, qreal);
    void sendParamsABC();
    void newSendParametrs(qreal, qreal, qreal, int);

private slots:
    void on_BoxChangeCharts_currentIndexChanged(int index);
    void on_StartButton_clicked();
    void on_PauseButton_clicked();
    void on_BreakButton_clicked();

    void getLoadParams(QVector<QString> vecLoadPar);


private:
    Ui::MainWindow *ui;
    Chart *chart;
    //QChartView *chartView;
    QTimer *m_timer;
    MyChartView *myview;

    QThread *initThread;


    qint8 m_countPressStart = 0;
    qint8 m_countPressPause = 0;
    qint8 m_countPressBreak = 0;
    qint8 m_countWindowResult = 0;

    qreal A = 0;
    qreal B = 0;
    qreal C = 0;
    qreal x = 0;



};
#endif // MAINWINDOW_H
