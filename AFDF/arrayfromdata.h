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
    Q_PROPERTY(double dataCountt READ dataCountt NOTIFY dataCounttChanged)


public:
    explicit ArrayFromData(QObject *parent = 0);

    Q_INVOKABLE void getTheFile(QString filePath);
    Q_INVOKABLE void reloadTheFile();

    Q_INVOKABLE QString getInputData(){ return inputData; }

    Q_INVOKABLE QString createArray();
    Q_INVOKABLE void saveArrayToFile(QString filepath);

    Q_INVOKABLE QString checkRowsAndColumns(int rows, int columns);

    Q_INVOKABLE QString createTable();
    Q_INVOKABLE void saveTableToFile(QString filepath);


    Q_INVOKABLE int rows(){ return m_rows; }
    void setRows(int rows){ m_rows = rows; }

    Q_INVOKABLE int columns(){ return m_columns; }
    void setColumns(int columns){ m_columns = columns; }

    double dataCountt(){ return dataCount; }
//    void setDataCountt(){ }


    Q_INVOKABLE void prepareVector(int rows, int columns){
        sortedTable.resize(rows);
        for (int i = 0; i < rows; i++){
            sortedTable[i].resize(columns);
        }
    }



private:
        QString inputData = "";
        QString outputData = "";
        double dataCount = 0;

        QString lastOpenedFile = "";

        QVector<double> unsortedTableValues;

        QVector<QVector<double> >sortedTable;

        int m_rows ;
        int m_columns;




signals:

        void rowsChanged();
        void columnsChanged();
        void dataCounttChanged();

public slots:
};

#endif // ARRAYFROMDATA_H
