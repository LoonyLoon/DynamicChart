#include "formresults.h"
#include "ui_formresults.h"

FormResults::FormResults(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormResults),
    model (new QStandardItemModel())
{
    ui->setupUi(this);

    connect(this, SIGNAL(setResult()),
            this, SLOT(setValueInTable()));


    model->setHorizontalHeaderLabels(horizonHeader);
}

FormResults::~FormResults()
{
    delete ui;
 //   delete model;
}

void FormResults::getValueInTable(QVector<qreal> xVector, QVector<qreal> yVector)
{
    m_xVector = xVector;
    m_yVector = yVector;

    emit setResult();
}

void FormResults::getParams(QVector<QString> paramsVector)
{
    item = new QStandardItem("Function:");
    model->setItem(0,0,item);

    item = new QStandardItem("A:");
    model->setItem(1,0,item);

    item = new QStandardItem("B:");
    model->setItem(2,0,item);

    item = new QStandardItem("C:");
    model->setItem(3,0,item);

    item = new QStandardItem("Step:");
    model->setItem(4,0,item);

    for (int i = 0; i < paramsVector.size(); ++i) {
        item = new QStandardItem(paramsVector.at(i));
        model->setItem(i,1,item);
    }
}

void FormResults::setValueInTable()
{

    int xrow = 5;
    int yrow = 5;
    for (int i = 0; i < m_xVector.size(); ++i) {
        xrow++;
        item = new QStandardItem(QString::number(m_xVector.at(i)));
          model->setItem(xrow,0,item);
    }

    for (int i= 0; i < m_yVector.size(); ++i) {
        yrow++;
        item = new QStandardItem(QString::number(m_yVector.at(i)));
        model->setItem(yrow,1,item);
    }

    ui->tableView->setModel(model);

}

void FormResults::on_SaveButton_clicked()
{

    QString pathTocsv=QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить как"),
                                              QDir::currentPath(),"Файл (*.csv)");
    QFile f(pathTocsv);

    if( f.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts(&f);
        QStringList strList;

      //  strList << "\" \"";
        for( int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c )
            strList << ui->tableView->model()->headerData(c, Qt::Horizontal).toString();
        ts << strList.join( ";" )+"\n";

        qDebug()<<"VerticalHeader"<<ui->tableView->verticalHeader()->count();
        qDebug()<<"HorHeader"<<ui->tableView->horizontalHeader()->count();
        for(int r = 0; r < ui->tableView->verticalHeader()->count(); ++r )
        {
            strList.clear();
//            strList << ui->tableView->model()->headerData(r, Qt::Vertical).toString();
            for( int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c )
            {
                strList <<ui->tableView->model()->data(ui->tableView->model()->index(r, c), Qt::DisplayRole).toString();
            }
            ts << strList.join( ";" )+"\n";
        }
        f.close();
    }



}

void FormResults::on_LoadButton_clicked()
{
    QVector<QString> loadParamVector;
    QVector<qreal> loadxVector;
    QVector<qreal> loadyVector;


    QFile file(QFileDialog::getOpenFileName(this,QString::fromUtf8("Выберите файл"),
                                                   QDir::currentPath(),"File csv (*.csv)"));

    if (file.open(QIODevice::ReadOnly)) {

        model->clear();
        model->setHorizontalHeaderLabels(horizonHeader);

        int lineindex = 0;                     // file line counter
        QTextStream in(&file);                 // read to text stream

          in.readLine(); //read first line (header)



        while (!in.atEnd()) {

            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();


            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(";", QString::SkipEmptyParts);

            qDebug()<<"SIZE"<<lineToken.size();
            // load parsed data to model accordingly
            for (int j = 0; j < lineToken.size(); j++) {
                QString value = lineToken.at(j);
                qDebug()<<"VALUE"<<value;
                QStandardItem *item = new QStandardItem(value);
                model->setItem(lineindex, j, item);
            }

            lineindex++;
        }

        file.close();
    }

    for(int i=0; i<=4; i++)
    {
        qDebug()<<"Params"<<model->item(i,1)->text();
        loadParamVector.push_back(model->item(i,1)->text());
    }

    for(int c=6; c < ui->tableView->verticalHeader()->count(); c++)
    {
        qDebug()<<"loadxVector"<<model->item(c,0)->text().toDouble();
        loadxVector.push_back(model->item(c,0)->text().toDouble());
    }

    for(int c=6; c < ui->tableView->verticalHeader()->count(); c++)
    {
        qDebug()<<"loadyVector"<<model->item(c,1)->text().toDouble();
        loadyVector.push_back( model->item(c,1)->text().toDouble());
    }

    emit sendLoadParams(loadParamVector,loadxVector, loadyVector);

}
