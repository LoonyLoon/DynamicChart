#ifndef FORMRESULTS_H
#define FORMRESULTS_H

#include <QWidget>
#include <QStandardItemModel>
#include <QVector>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

namespace Ui {
class FormResults;
}

class FormResults : public QWidget
{
    Q_OBJECT

public:
    explicit FormResults(QWidget *parent = nullptr);
    ~FormResults();

private:
    Ui::FormResults *ui;
    QStandardItemModel *model;
    QStandardItem *item;

    QVector<qreal> m_xVector;
    QVector<qreal> m_yVector;

    QStringList horizonHeader = {"X", "Y"};


private slots:
    void getValueInTable(QVector<qreal> xVector, QVector<qreal> yVector);
    void setValueInTable();
    void getParams(QVector<QString> paramsVector);

    void on_SaveButton_clicked();

    void on_LoadButton_clicked();

signals:
    void setResult();
    void sendLoadParams(QVector<QString>,QVector<qreal>,QVector<qreal>);
};

#endif // FORMRESULTS_H
