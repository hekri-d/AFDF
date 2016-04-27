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
    inputData = "";


    QString fileName = QQmlFile::urlToLocalFileOrQrc(filePath);

    QFile inputFile(fileName);


//                qDebug()<<"Emni i fileNamet eshte:  "<<fileName<<"filePath: "<<filePath;


    if(!(inputFile.open(QIODevice::ReadOnly))){
//                qDebug()<<"Didn't work: "<<inputFile.errorString();
    }
    else if (!inputFile.error()) {
//                qDebug()<<"It finally worked: "<<inputFile.errorString();
    }


    /* =========================== CAN'T TOUCH THIS >><< END ============ */
//    QString shemsi;

    QString inputString;
//qDebug()<<"It finally worked: over while ";
//shemsi = inputFile.readAll();/*shemsi =shemsi.replace(QString("."), QString(","));*/
    while ( !( inputFile.atEnd() ) ){
//    qDebug()<<"It finally worked: inside while head";
        inputString = inputFile.readLine(); /*inputString =  inputString.replace(QString(","), QString("."));*/

        unsortedTableValues.push_back(inputString.toDouble());

        dataCount++;
//        qDebug()<<"It finally worked: inside while bottom";
    }

//qDebug()<<"It finally worked: under while";

qDebug()<<"Rows get file: "<<m_rows;
qDebug()<<"Columns: "<<m_columns;

//    qDebug()<<inputString<<endl;




//inputString.replace(QString("."), QString(","));

//qDebug()<<inputString<<endl;


    for (QVector<double>::iterator iteratori = unsortedTableValues.begin();
                        iteratori < unsortedTableValues.end();
                                            iteratori++){
        inputData +="\n"+ QString::number(*iteratori);
    }


//qDebug()<<shemsi;/*<<;*//*endl;*/

//inputData = shemsi;

    fileName.clear();


}



QString ArrayFromData::getInputData(){
    return inputData;
}



QString ArrayFromData::createArray(/*int m_rows, int m_columns*/){

    QTextStream seeout(&outputData);

    outputData = "";
    inputData = "";

    int c =0;

    for (int i =0; i<m_columns; i++){qDebug()<<"worked: "<<i<<dataCount;
        for (int j=0; j<m_rows; j++){

            sortedTable[j][i] = unsortedTableValues[c];
            c++;
            if( c >= dataCount){qDebug()<<"Bitch it reached it: "; break;}
        }
        if( c >= dataCount){qDebug()<<"Bitch it reached it: "; break;}

    }

    qDebug()<<"Rows create array: "<<m_rows;
    qDebug()<<"Columns: "<<m_columns;

//    outputData = "";

    size_t s = 0;

    for (int i = 0; i < m_rows; i++){
        qDebug()<<"It is: "<<sortedTable[i][0];
    }




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



QString ArrayFromData::checkRowsAndColumns(int rows, int columns){

    QString report = "?";

    if(dataCount < rows * columns){
        report = "The file you provided doesn't have enough data to create an array of the size " + QString::number(rows) + " by " + QString::number(columns);
    }
    else if(dataCount > rows * columns) {
        report = "The file you provided has more data than are needed to create an array of the size "  + QString::number(rows) + " by " + QString::number(columns);
    }
    else if(dataCount = rows * columns){
        report = "The file has the right amount of data.";
    }

    return report;
}



