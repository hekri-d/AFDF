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

    Q_INVOKABLE QString getOutputData();
    Q_INVOKABLE void saveArrayToFile(QString filepath/*, const QString &fileType*/);

private:
        QString inputData;
        QString outputData;

        QVector<double> unsortedTableValues;
        double sortedTable[35][10];





signals:

public slots:
};

#endif // ARRAYFROMDATA_H
