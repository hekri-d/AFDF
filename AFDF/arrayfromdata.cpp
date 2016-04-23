#include "arrayfromdata.h"

#include <QVector>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QUrl>
#include <QTextStream>

#include <QtGui/QTextDocument>
#include <QtGui/QTextCursor>
#include <QtGui/QFontDatabase>
#include <QtCore/QFileInfo>

#include "qqmlfile.h"

ArrayFromData::ArrayFromData(QObject *parent) : QObject(parent)
{

}

void ArrayFromData::getTheFile(QString filePath){

    /* =========================== CAN'T TOUCH THIS ============ */


    dataSize = 0;

    QString fileName = QQmlFile::urlToLocalFileOrQrc(filePath);

    QFile inputFile(fileName);

                qDebug()<<"Emni i fileNamet eshte:  "<<fileName<<"filePath: "<<filePath;


    if(!(inputFile.open(QIODevice::ReadOnly))){
                qDebug()<<"Didn't work: "<<inputFile.errorString();
    }
    else if (!inputFile.error()) {
                qDebug()<<"It finally worked: "<<inputFile.errorString();
    }


    /* =========================== CAN'T TOUCH THIS >><< END ============ */

    QString inputString;
qDebug()<<"It finally worked: ";

    do {
    qDebug()<<"It finally worked: ";
        inputString = inputFile.readLine();
        unsortedTableValues.push_back(inputString.toDouble());
        dataSize++;
        qDebug()<<"It finally worked: ";
    }while (!(inputFile.atEnd()));

qDebug()<<"It finally worked: ";



    int c =0;

    for (int i =0; i<(columns); i++){qDebug()<<"worked: ";
        for (int j=0; j<rows; j++){

            sortedTable[j][i] = unsortedTableValues[c];
            c++;
        }

    }




    for (QVector<double>::iterator iteratori = unsortedTableValues.begin();
                        iteratori < unsortedTableValues.end();
                                            iteratori++){
        inputData +="\n"+ QString::number(*iteratori);
    }



}



QString ArrayFromData::getTheData(){
    return inputData;
}



QString ArrayFromData::createArray(/*int rows, int columns*/){

    QTextStream seeout(&outputData);

    outputData = "";

    int s = 0;

    seeout<<"{";

    for (int i =0; i<rows; i++){
        seeout<<"\t{ ";

        for (int j=0; j<columns; j++){
            seeout<<sortedTable[i][j];

            if(!(j == (columns-1) ))
                seeout <<", ";

            s = j;
        }

        seeout <<"}";

        if(s==(columns-1) && i !=(rows-1)){seeout<<",";  }
        else if(s==(columns-1) && i ==(rows-1)){ seeout <<"\t};"; }

        seeout << endl;

    }

    return outputData;

}



void ArrayFromData::saveArrayToFile(QString filepath/*, const QString &fileType*/){

    QString localPath = QQmlFile::urlToLocalFileOrQrc(filepath);
    QFile saveArrayFile(localPath);
    if (!saveArrayFile.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug()<<"Sum ting wong";
        qDebug()<<saveArrayFile.errorString();
        return;
    }

        QTextStream seeout(&saveArrayFile);

        int s = 0;

        seeout<<"{";

        for (int i =0; i<rows; i++){
            seeout<<"\t{ ";

            for (int j=0; j<columns; j++){
                seeout<<sortedTable[i][j];

                if(!(j == (columns-1) ))
                    seeout <<", ";

                s = j;
            }

            seeout <<"}";

            if(s==(columns-1) && i !=(rows-1)){seeout<<",";  }
            else if(s==(columns-1) && i ==(rows-1)){ seeout <<"\t};"; }

            seeout << endl;

        }
qDebug()<<"Sum ting wong 12";

}


QString ArrayFromData::checkDimensions(int rows, int columns){

    QString report = "?";

    if(dataSize < rows * columns){
        report = "The file you provided doesn't have enough data to create an array of the size " + QString::number(rows) + " by " + QString::number(columns);
    }
    else if(dataSize > rows * columns) {
        report = "The file you provided has more data than are needed to create an array of the size "  + QString::number(rows) + " by " + QString::number(columns);
    }
    else if(dataSize = rows * columns){
        report = "The file has the right amount of data.";
    }

    return report;
}




























