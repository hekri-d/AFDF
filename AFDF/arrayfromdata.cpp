#include "arrayfromdata.h"

#include <QVector>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QUrl>
#include <QTextStream>

#include "qqmlfile.h"

ArrayFromData::ArrayFromData(QObject *parent) : QObject(parent)
{

}

void ArrayFromData::getTheFile(QString filePath){

    /* =========================== CAN'T TOUCH THIS ============ */

    QVector<double> unsortedTableValues;

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


    while (!(inputFile.atEnd())) {
        inputString = inputFile.readLine();
        unsortedTableValues.push_back(inputString.toDouble());
    }



//    double sortedTable[35][10];


    int c =0;

    for (int i =0; i<10; i++){
        for (int j=0; j<35; j++){

            sortedTable[j][i] = unsortedTableValues[c];
            c++;
        }

    }


    QFile outputFile("/home/ihaaaaa/Desktop/outFromQt.txt");

    if(outputFile.open(QFile::WriteOnly | QFile::Truncate )){

        QTextStream seeout(&outputFile);


        int s = 0;

        seeout<<"{";

        for (int i =0; i<35; i++){

            seeout<<"\t{ ";


            for (int j=0; j<10; j++){

                seeout<<sortedTable[i][j];


                if(!(j == 9))
                    seeout <<", ";


                s = j;
            }


            seeout <<"}";

            if(s==9 && i !=34){seeout<<","; }

            else if(s==9 && i ==34){ seeout <<"\t};";  }
            seeout << endl;

        }


//        outputData = outputString;


    }

//    QString inputDisplayString = "";

    for (QVector<double>::iterator iteratori = unsortedTableValues.begin();
                        iteratori < unsortedTableValues.end();
                                            iteratori++){
        inputData +="\n"+ QString::number(*iteratori);
    }


//    inputData = inputDisplayString;






    inputFile.close();
    outputFile.close();
}



QString ArrayFromData::getTheData(){
    return inputData;
}



QString ArrayFromData::getOutputData(){
    return outputData;

}



void ArrayFromData::saveArrayToFile(QString filepath){

    QString fileName = QQmlFile::urlToLocalFileOrQrc(filepath);

    QFile outputFile(fileName);

//    QVector<double> unsortedTableValues;



    if(outputFile.open(QFile::WriteOnly | QFile::Truncate )){

        QTextStream seeout(&outputFile);


        int s = 0;

        seeout<<"{";

        for (int i =0; i<35; i++){

            seeout<<"\t{ ";


            for (int j=0; j<10; j++){

                seeout<<sortedTable[i][j];


                if(!(j == 9))
                    seeout <<", ";


                s = j;
            }


            seeout <<"}";


            if(s==9 && i !=34){seeout<<",";  }

            else if(s==9 && i ==34){ seeout <<"\t};"; }
            seeout << endl;

        }


//        outputData = outputString;
}

}
