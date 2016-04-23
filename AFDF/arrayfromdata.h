#ifndef ARRAYFROMDATA_H
#define ARRAYFROMDATA_H

#include <QObject>
#include <QUrl>
#include <QString>
#include <QVector>
class ArrayFromData : public QObject
{
    Q_OBJECT
public:
    explicit ArrayFromData(QObject *parent = 0);

    Q_INVOKABLE void getTheFile(QString filePath);

    Q_INVOKABLE QString getTheData();

    Q_INVOKABLE QString createArray(/*int rows, int columns*/);
    Q_INVOKABLE void saveArrayToFile(QString filepath/*, const QString &fileType*/);
    Q_INVOKABLE QString checkDimensions(int rows, int columns);

//    Q_PROPERTY(int arrayDimensions READ arrayDimensions WRITE setArrayDimensions NOTIFY arrayDimensionsChanged)
    Q_INVOKABLE void getArrayDimensions(int rows, int columns){

        this->rows = rows;
        this->columns = columns;
    }

private:
        QString inputData = "";
        QString outputData = "";

        QVector<double> unsortedTableValues;
        double sortedTable[35][10];
        double dataSize;
        int rows = 0;
        int columns = 0;





signals:

public slots:
};

#endif // ARRAYFROMDATA_H
