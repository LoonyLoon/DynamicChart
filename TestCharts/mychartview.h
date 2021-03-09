#ifndef MYCHARTVIEW_H
#define MYCHARTVIEW_H

#include "formresults.h"

#include <QtCharts/QChartView>
#include <QChart>
#include <QTableWidget>
#include <QVector>
#include <QDebug>



class MyChartView : public QtCharts::QChartView
{
    Q_OBJECT
public:
    MyChartView(QtCharts::QChart *chart, QWidget *parent = nullptr);
    virtual ~MyChartView();



public slots:
    void OpenWidgetResults(int index);


protected:
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    FormResults *form;

    int m_openWindowResults = 0;

private slots:
    void getResult(QVector<qreal> xVector, QVector<qreal> yVector);
    void getParams(QVector<QString> paramsVector);
    void getLoadParams(QVector<QString> loadParams, QVector<qreal> xLoadVec, QVector<qreal> yLoadVec);

signals:
    void sendResults(QVector<qreal>, QVector<qreal>);
    void sendParams(QVector<QString>);
    void sendLoadParams(QVector<QString>);
    void sendLoadXY(QVector<qreal>,QVector<qreal>);

};


#endif // MYCHARTVIEW_H
