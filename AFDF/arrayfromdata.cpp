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

    if(!(inputFile.open(QIODevice::ReadOnly))){
    }
    else if (!inputFile.error()) {
    }


    /* =========================== CAN'T TOUCH THIS >><< END ============ */


    QString inputString;
    while ( !( inputFile.atEnd() ) ){
        inputString = inputFile.readLine();
        inputString =  inputString.replace(QString(","), QString("."));
        unsortedTableValues.push_back(inputString.toDouble());
        dataCount++;
    }



qDebug()<<"Rows get file: "<<m_rows;
qDebug()<<"Columns: "<<m_columns;


    for (QVector<double>::iterator iteratori = unsortedTableValues.begin();
                                                iteratori < unsortedTableValues.end();
                                                                                iteratori++){
        inputData +=QString::number(*iteratori)+"\n";
    }


//    fileName.clear();


}



QString ArrayFromData::getInputData(){
    return inputData;
}


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

    for (int i = 0; i < m_columns; i++){qDebug()<<"worked: "<<i<<dataCount;
        for (int j = 0; j < m_rows; j++){

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



    for (int i =0; i<m_rows; i++){
        seeout<<"\t ";

        for (int j=0; j<m_columns; j++){
            seeout<< QString("%1").arg(sortedTable[i][j] ).rightJustified(8,' ');

            if(!(j == (m_columns-1) ))
                seeout <<", ";

            s = j;
        }


        if(s==(m_columns-1) && i !=(m_rows-1)){seeout<<",";  }
        else if(s==(m_columns-1) && i ==(m_rows-1)){ seeout <<"\t;"; }

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
qDebug()<<"Sum ting wong 12";

}

void ArrayFromData::saveTableToFile(QString filepath/*, const QString &fileType*/){

    QString localPath = QQmlFile::urlToLocalFileOrQrc(filepath);
    QFile saveArrayFile(localPath);
    if (!saveArrayFile.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug()<<"Sum ting wong";
        qDebug()<<saveArrayFile.errorString();
        return;
    }

        QTextStream seeout(&saveArrayFile);

        int s = 0;

//        seeout<<"{";

        for (int i = 0; i < m_rows; i++){
            seeout<<"\t ";

            for (int j = 0; j < m_columns; j++){
                seeout<< QString("%1").arg(sortedTable[i][j] ).rightJustified(7,' ');

                if(!(j == (m_columns-1) ))
//                    seeout <<", ";

                s = j;
            }

//            seeout <<"}";

            if(s==(m_columns-1) && i != (m_rows-1)){seeout<<",";  }
            else if(s==(m_columns-1) && i ==(m_rows-1)){ seeout <<"\t;"; }

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



