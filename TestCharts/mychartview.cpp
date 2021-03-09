#include "mychartview.h"


MyChartView::MyChartView(QtCharts::QChart *chart, QWidget *parent) :
    QtCharts::QChartView(chart, parent),
    form(new FormResults())
{

    connect(this, SIGNAL(sendResults(QVector<qreal>, QVector<qreal>)),
            form, SLOT(getValueInTable(QVector<qreal>, QVector<qreal>)));

    connect(this, SIGNAL(sendParams(QVector<QString>)),
            form, SLOT(getParams(QVector<QString>)));

    connect(form, SIGNAL(sendLoadParams(QVector<QString>,QVector<qreal>,QVector<qreal>)),
            this, SLOT(getLoadParams(QVector<QString>, QVector<qreal>, QVector<qreal>)));


}

MyChartView::~MyChartView()
{
    delete form;
}

void MyChartView::OpenWidgetResults(int index)
{
    m_openWindowResults = index;
}

void MyChartView::mousePressEvent(QMouseEvent *event)
{
 if(m_openWindowResults == 1 && event->buttons() & Qt::LeftButton)
 {
     form->show();
 }
}

void MyChartView::getResult(QVector<qreal> xVector, QVector<qreal> yVector)
{

    emit sendResults(xVector, yVector);
}

void MyChartView::getParams(QVector<QString> paramsVector)
{
    emit sendParams(paramsVector);
}

void MyChartView::getLoadParams(QVector<QString> loadParams, QVector<qreal> xLoadVec, QVector<qreal> yLoadVec)
{
 if(!xLoadVec.empty() && !yLoadVec.empty())
 {
     emit sendLoadParams(loadParams);
     emit sendLoadXY(xLoadVec, yLoadVec);
 }
}
