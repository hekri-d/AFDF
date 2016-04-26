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


    dataCount = 0;

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
qDebug()<<"It finally worked: over while ";

    while ( !( inputFile.atEnd() ) ){
    qDebug()<<"It finally worked: inside while head";
        inputString = inputFile.readLine();
        unsortedTableValues.push_back(inputString.toDouble());
        dataCount++;
        qDebug()<<"It finally worked: inside while bottom";
    }

qDebug()<<"It finally worked: under while";

qDebug()<<"Rows: "<<m_rows;
qDebug()<<"Columns: "<<m_columns;


    for (QVector<double>::iterator iteratori = unsortedTableValues.begin();
                        iteratori < unsortedTableValues.end();
                                            iteratori++){
        inputData +="\n"+ QString::number(*iteratori);
    }



}



QString ArrayFromData::getInputData(){
    return inputData;
}



QString ArrayFromData::createArray(/*int m_rows, int m_columns*/){

    QTextStream seeout(&outputData);

    int c =0;

    for (int i =0; i<m_columns; i++){qDebug()<<"worked: "<<i<<dataCount;
        for (int j=0; j<m_rows; j++){

            sortedTable[j][i] = unsortedTableValues[c];
            c++;
            if( c >= dataCount){qDebug()<<"Bitch it reached it: "; break;}
        }
        if( c >= dataCount){qDebug()<<"Bitch it reached it: "; break;}

    }



    outputData = "";

    int s = 0;

    seeout<<"{";

    for (int i =0; i<m_rows; i++){
        seeout<<"\t{ ";

        for (int j=0; j<m_columns; j++){
            seeout<<sortedTable[i][j];

            if(!(j == (m_columns-1) ))
                seeout <<", ";

            s = j;
        }

        seeout <<"}";

        if(s==(m_columns-1) && i !=(m_rows-1)){seeout<<",";  }
        else if(s==(m_columns-1) && i ==(m_rows-1)){ seeout <<"\t};"; }

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

        for (int i =0; i<m_rows; i++){
            seeout<<"\t{ ";

            for (int j=0; j<m_columns; j++){
                seeout<<sortedTable[i][j];

                if(!(j == (m_columns-1) ))
                    seeout <<", ";

                s = j;
            }

            seeout <<"}";

            if(s==(m_columns-1) && i !=(m_rows-1)){seeout<<",";  }
            else if(s==(m_columns-1) && i ==(m_rows-1)){ seeout <<"\t};"; }

            seeout << endl;

        }
qDebug()<<"Sum ting wong 12";

}

