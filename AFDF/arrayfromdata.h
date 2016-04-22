#ifndef ARRAYFROMDATA_H
#define ARRAYFROMDATA_H

#include <QObject>
#include <QUrl>
#include <QString>
class ArrayFromData : public QObject
{
    Q_OBJECT
public:
    explicit ArrayFromData(QObject *parent = 0);

    Q_INVOKABLE void getTheFile(QString filePath);

    Q_INVOKABLE QString getTheData();

    Q_INVOKABLE QString getOutputData();

private:
        QString inputData;
        QString outputData;


signals:

public slots:
};

#endif // ARRAYFROMDATA_H
