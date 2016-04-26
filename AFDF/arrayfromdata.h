#ifndef ARRAYFROMDATA_H
#define ARRAYFROMDATA_H

#include <QObject>
#include <QUrl>
#include <QString>
#include <QVector>
#include <QDebug>
class ArrayFromData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)


public:
    explicit ArrayFromData(QObject *parent = 0);

    Q_INVOKABLE void getTheFile(QString filePath);

    Q_INVOKABLE QString getInputData();

    Q_INVOKABLE QString createArray(/*int rows, int columns*/);
    Q_INVOKABLE void saveArrayToFile(QString filepath/*, const QString &fileType*/);
//    Q_INVOKABLE QString checkDimensions(int rows, int columns);


    Q_INVOKABLE void getArrayDimensions(int rows, int columns){

//        this->rows = rows;
//        this->columns = columns;
    }


    int rows(){
        return m_rows;
    }
    int columns(){
        return m_columns;
    }

    void setRows(int rows){
        m_rows = rows;
    }

    void setColumns(int columns){
        m_columns = columns;
    }

private:
        QString inputData = "";
        QString outputData = "";

        QVector<double> unsortedTableValues;
        double sortedTable[35][10];
        double dataCount;
        int m_rows = 0;
        int m_columns = 0;





signals:

        void rowsChanged();
        void columnsChanged();

public slots:
};

#endif // ARRAYFROMDATA_H
