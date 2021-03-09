#include "chart.h"

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis())//,
//    m_step(0),
//    m_x(5),
//    m_y(1)
{
//    m_series = new QSplineSeries(this);
//    QPen green(Qt::red);
//    green.setWidth(3);
//    m_series->setPen(green);
////    m_series->append(1, 5);

//    addSeries(m_series);

////    addAxis(m_axisX,Qt::AlignBottom);
//    addAxis(m_axisY,Qt::AlignLeft);
//    m_series->attachAxis(m_axisX);
//    m_series->attachAxis(m_axisY);
////    m_axisX->setTickCount(5);
////    m_axisX->setRange(-10, 10);
//    m_axisY->setRange(-10, 10);



    m_series = new QSplineSeries(this);

        QPen green(Qt::red);
        green.setWidth(3);
        m_series->setPen(green);
//        m_series->append(m_x, m_y);

        addSeries(m_series);
        createDefaultAxes();
      //  setAxisX(m_axisY, m_series);
        m_axisY->setTickCount(5);

        yMax = 10;
        yMin = -5;

        xMax = 10;
        xMin = -10;

        axisX()->setRange(xMin, xMax);
        axisY()->setRange(yMin, yMax);

        connect(m_series, &QSplineSeries::pointAdded, [=](int index){
                qreal y = m_series->at(index).y();

                if(y< yMin || y > yMax){
                    if(y < yMin)
                        yMin = y;
                    if(y> yMax)
                        yMax = y;
                    axisY()->setRange(yMin-20, yMax+20);
                }

            });

        connect(m_series, &QSplineSeries::pointAdded, [=](int index){
                qreal x = m_series->at(index).x();
                qDebug()<<"IKS X"<<x;

                if(x< xMin || x > xMax){
                    if(x < xMin)
                        xMin = x;
                    if(x> xMax)
                        xMax = x;
                    axisX()->setRange(xMin-20, xMax+20);
                }

            });

}


Chart::~Chart()
{
    delete m_axisX;
    delete m_axisY;
    delete m_series;
}

void Chart::setFunction(int indexChart)
{
    m_function = indexChart;
}

void Chart::setParametrs(qreal A, qreal B, qreal C, qreal step)
{
    m_A = A;
    m_B = B;
    m_C = C;
    x = step;
    m_Step = step;
    qDebug()<<"xxx"<<m_A;
}

void Chart::sendParamsToTable()
{

    switch (m_function) {
    case 0:
        m_sendfunction = "f(x)=A*(x*x)+B*x+C";
        break;
    case 1:
        m_sendfunction = "f(x)=A*sin(x)+B*cos(C*x)";
        break;
    case 2:
        m_sendfunction = "f(x)=A*log(B*x)";
        break;
    case 3:
        m_sendfunction = "f(x)=A/(sin(x*x)*B)";
        break;
    }

    paramsVector.push_back(m_sendfunction);
    paramsVector.push_back(QString::number(m_A));
    paramsVector.push_back(QString::number(m_B));
    paramsVector.push_back(QString::number(m_C));
    paramsVector.push_back(QString::number(m_Step));


    emit sendToTableParams(paramsVector);
}

void Chart::calculation()
{

    m_series->append(x, y);
//    scroll(x, y);
    xVector.push_back(x);
    yVector.push_back(y);
    x+=m_Step;


    emit sendToTable(xVector, yVector);

    qDebug()<<"calculation() x =" << x;
}

void Chart::getNewParams(qreal A, qreal B, qreal C, int index)
{
    m_function = index;
    m_A = A;
    m_B = B;
    m_C = C;
}

void Chart::repaint(QVector<qreal> xVec, QVector<qreal> yVec)
{
    m_series->clear();
    for (int i = 0; i < xVec.size(); i++)
    {
         m_series->append(xVec.at(i), yVec.at(i));
    }
    x = xVec.back();
    m_Step = xVec.at(1) - xVec.at(0);
    xVector.swap(xVec);
    yVector.swap(yVec);
}

void Chart::quadraticFunction()
{
   qDebug()<<"quadraticFunction";
    y = m_A*(x*x)+m_B*x+m_C;
     qDebug()<<"quadraticFunction y = " << y
             << "A" << m_A;
    calculation();
}

void Chart::sincosFunction()
{
    y = m_A*sin(x)+m_B*cos(m_C*x);
    qDebug()<<"sincos Y"<< y;
    calculation();
}

void Chart::logFunction()
{
     y = m_A*log(m_B*x);
     calculation();

}

void Chart::sinFunction()
{
    y = m_A/(sin(x*x)*m_B);
    calculation();
}

void Chart::PaintChart()
{

    switch (m_function) {
    case 0:
          quadraticFunction();
        break;
    case 1:
          sincosFunction();
        break;
    case 2:
          logFunction();
        break;
    case 3:
          sinFunction();
        break;
    }
    qDebug()<<"INDEX CHART"<<m_function;
}


