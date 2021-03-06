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

#include <iostream>
#include "qqmlfile.h"

using namespace std;

ArrayFromData::ArrayFromData(QObject *parent) : QObject(parent)
{

}



/* FIX THE OTHER FUNCTIONS TO FIT 'getTheFile' (DIFFERENTIATE BETWEEN DOUBLES  AND STRINGS ON THE INPUT DATA FILE) */

void ArrayFromData::getTheFile(QString filePath, int inputKind ){

    /* inputKind --> Comes from the inputCombobox. Determines what kind of data is to be loaded (doubles or text)*/

    /* =========================== CAN'T TOUCH THIS ============ */

    dataCount = 0;
    inputData = "";
    outputData = "";
    inputData = "";

    unsortedTableValues.clear();


    QString fileName = QQmlFile::urlToLocalFileOrQrc(filePath);

    lastOpenedFile = fileName;

    QFile inputFile(fileName);


    if(!(inputFile.open(QIODevice::ReadOnly))){
    }
    else if (inputFile.error()) {
        qDebug()<<inputFile.errorString()<<endl;
    }


    /* =========================== CAN'T TOUCH THIS >><< END ============ */

    if ( inputKind == 0 ) {

        QString inputString;
        while ( !( inputFile.atEnd() ) ){
            inputString = inputFile.readLine();
            inputString = inputString.replace(QString(","), QString("."));
            unsortedTableValues.push_back(inputString.toDouble());
            dataCount++;
        }



        for (QVector<double>::iterator iteratori = unsortedTableValues.begin();
                                                                 iteratori < unsortedTableValues.end();
                                                                                                    iteratori++){
            inputData +=QString::number(*iteratori)+"\n";

        }

    }

    else if (inputKind == 1){
        QString inputString;

        while ( !( inputFile.atEnd() ) ){
            inputString = inputFile.readLine();
            unsortedTextTableValues.push_back(inputString);
            dataCount++;
        }

        for (QVector<QString>::iterator iterator = unsortedTextTableValues.begin(); iterator < unsortedTextTableValues.end(); iterator++ ){
            inputData += *iterator + "\n";
        }
    }

    inputFile.close();
}

/*====================================================================================================================*/


void ArrayFromData::reloadTheFile(){

    /* =========================== CAN'T TOUCH THIS ============ */

    dataCount = 0;
    inputData = "";
    outputData = "";

    unsortedTableValues.clear();

    QFile inputFile(lastOpenedFile);


    if((inputFile.open(QIODevice::ReadOnly))){
        qDebug()<<"OPened"<<endl;
    }
    else if (inputFile.error()) {
        qDebug()<<inputFile.errorString()<<endl;
    }


    /* =========================== CAN'T TOUCH THIS >><< END ============ */


    QString inputString;
    while ( !( inputFile.atEnd() ) ){
        inputString = inputFile.readLine();
        inputString = inputString.replace(QString(","), QString("."));
        unsortedTableValues.push_back(inputString.toDouble());
        dataCount++;
    }



    for (QVector<double>::iterator iteratori = unsortedTableValues.begin();
         iteratori < unsortedTableValues.end();
         iteratori++){
        inputData +=QString::number(*iteratori)+"\n";

        qDebug()<<"this: "<<*(iteratori)<<"\n";
    }



    inputFile.close();

}


/* ========================================================================================================================*/



/*================= CREATE ARRAY - START ============================*/

QString ArrayFromData::createArray(){

    QTextStream seeout(&outputData);

    outputData = "";
    inputData = "";

    int c =0;

    for (int i = 0; i < m_columns; i++){qDebug()<<"worked: "<<i<<dataCount;
        for (int j = 0; j < m_rows; j++){

            sortedTable[j][i] = unsortedTableValues[c];
            c++;
            if( c >= dataCount){qDebug()<<"Bitch it reached it: "; break;}
        }
        if( c >= dataCount){qDebug()<<"Bitch it reached it: "; break;}

    }

    size_t s = 0;

    for (int i = 0; i < m_rows; i++){
        qDebug()<<"It is: "<<sortedTable[i][0];
    }




    seeout<<"{";

    for (int i =0; i<m_rows; i++){
        seeout<<"\t{ ";

        for (int j=0; j<m_columns; j++){
            seeout<< QString("%1").arg(sortedTable[i][j] ).rightJustified(8,' ');

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

/*================= CREATE ARRAY - END ============================*/



QString ArrayFromData::createTable(){

    QTextStream seeout(&outputData);

    outputData = "";
    inputData = "";

    int c =0;

    for (int i = 0; i < m_rows; i++){
        for (int j = 0; j < m_columns; j++){

            sortedTable[i][j] = unsortedTableValues[c];
            c++;

        }


    }

    size_t s = 0;

    for (int i =0; i<m_rows; i++){
        seeout<<"\t ";

        for (int j=0; j<m_columns; j++){
            seeout<< QString("%1").arg(sortedTable[i][j] ).rightJustified(1,' ');

            if(!(j == (m_columns-1) ))
                seeout <<", ";

            s = j;
        }



        if(s==(m_columns-1) && i ==(m_rows-1)){ seeout <<"\t"; }

        seeout << endl;

    }

    return outputData;

}




void ArrayFromData::saveArrayToFile(QString filepath){

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

    for (int i = 0; i < m_rows; i++){
        seeout<<"\t{ ";

        for (int j = 0; j < m_columns; j++){
            seeout<< QString("%1").arg(sortedTable[i][j] ).rightJustified(7,' ');

            if(!(j == (m_columns-1) ))
                seeout <<", ";

            s = j;
        }

        seeout <<"}";

        if(s==(m_columns-1) && i != (m_rows-1)){seeout<<",";  }
        else if(s==(m_columns-1) && i ==(m_rows-1)){ seeout <<"\t};"; }

        seeout << endl;

    }

}




void ArrayFromData::saveTableToFile(QString filepath){

    QString localPath = QQmlFile::urlToLocalFileOrQrc(filepath);
    QFile saveTableFile(localPath);

    if (!saveTableFile.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug()<<"Sum ting wong";
        qDebug()<<saveTableFile.errorString();
        return;
    }

    QTextStream seeout(&saveTableFile);

    for (int i = 0; i < m_rows; i++){

        for (int j = 0; j < m_columns; j++){
            seeout<< QString("%1").arg(sortedTable[i][j] ).rightJustified(1,' ');

            if(!(j == (m_columns-1) ))
                seeout <<", ";

        }

        seeout << endl;

    }

}




QString ArrayFromData::checkRowsAndColumns(int rows, int columns){

    QString report = "?";

    if(dataCount < (rows * columns) ){
        report = "The file you provided doesn't have enough data to create an array of the size " + QString::number(rows) + " by " + QString::number(columns);
    }
    else if(dataCount > (rows * columns) ){
        report = "The file you provided has more data than are needed to create an array of the size "  + QString::number(rows) + " by " + QString::number(columns);
    }
    else if(dataCount == (rows * columns) ){
        report = "The file has the right amount of data.";
    }

    return report;
}



