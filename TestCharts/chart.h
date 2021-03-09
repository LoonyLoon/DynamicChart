#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QDebug>
#include <QtMath>
#include <QVector>


QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart : public QChart
{
   Q_OBJECT
public:
    Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    virtual ~Chart();


public slots:
    void setParametrs(qreal A, qreal B, qreal C, qreal step);
    void sendParamsToTable();


private:

    QSplineSeries *m_series;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;

    qreal m_A = 0;
    qreal m_B = 0;
    qreal m_C = 0;
    qreal m_Step = 0;
    qreal x = 0;
    qreal y = 0;

    QVector<qreal> xVector;
    QVector<qreal> yVector;
    QVector<QString> paramsVector;

    int m_function = 0;


    qreal yMin;
    qreal yMax;

    qreal xMin;
    qreal xMax;

    QString m_sendfunction;

 private slots:
        void PaintChart();
        void setFunction(int indexChart);
        void quadraticFunction();
        void sincosFunction();
        void logFunction();
        void sinFunction();
        void calculation();
        void getNewParams(qreal A, qreal B, qreal C, int index);
        void repaint(QVector<qreal> xVec, QVector<qreal> yVec);

signals:
       void sendToTable(QVector<qreal>, QVector<qreal>);
       void sendToTableParams(QVector<QString>);
//       void sendToTableParams(QVector<QString>);

};


#endif // CHART_H
