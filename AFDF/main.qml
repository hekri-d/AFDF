//import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import QtQuick 2.4
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4

import ArrayFromData 1.0


Window {
    visible: true
    width: Screen.width/1.5
    height: Screen.height/1.8
//    implicitWidth:



        ArrayFromData{
            id: arrayFromData;
        }


        FileDialog {
            id: fileDialog
            title: "Please choose a file"
            folder: shortcuts.home

            onAccepted: {


                arrayFromData.getTheFile(fileDialog.fileUrls)
                inputData.text = arrayFromData.getInputData();

            }
            onRejected: {
                console.log("Canceled")

            }

        }




        Item {
            id: mainItem
            width: 780
            anchors.fill: parent

            Button {
                id: load
                y: 97
                text: qsTr("Load File")
                anchors.left: inputData.left
                anchors.leftMargin: 0
                anchors.bottom: inputData.top
                anchors.bottomMargin: 10

//                enabled:

                onClicked: {
                    inputData.text = ""

                    arrayFromData.getArrayDimensions(rowsComboBox.currentIndex, columnsComboBox.currentIndex)
//                    arrayFromData.checkDimensions(rowsComboBox.currentIndex, columnsComboBox.currentIndex)
                    fileDialog.open()

                }
            }

            Button {
                id: edit
                y: 97
                text: qsTr("Edit")
                anchors.bottom: output.top
                anchors.bottomMargin: 10
                anchors.verticalCenterOffset: 0
                anchors.verticalCenter: load.verticalCenter
                anchors.left: output.left
                anchors.leftMargin: 0

                        onClicked: {
                    output.readOnly = 0
                }
            }

            TextArea {
                id: inputData
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: output.bottom
                anchors.bottomMargin: 0
                anchors.top: output.top
                anchors.topMargin: 0
                anchors.right: output.left
                anchors.rightMargin: 10
            }



            TextArea {
                id: output
                x: 564
                y: 335
                width: (mainItem.width/2)-15
                height: mainItem.height*0.58
                text: "tfuyjfgyh"
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.bottom: quit.top
                anchors.bottomMargin: 30
                readOnly: true
                wrapMode: TextEdit.NoWrap
        //            horizontalScrollBarPolicy:
            }

            Button {
                id: quit
                x: 348
                y: 368
                text: qsTr("Quit")
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20

                onClicked: Qt.quit()
            }


        //TODO: Remove this FileDialog and implement the same functionality in the first FileDialog
            FileDialog {
                id: saveFileDialog
                selectExisting: false
                selectFolder: false

                onAccepted: arrayFromData.saveArrayToFile(saveFileDialog.fileUrls)

            }

            Button {
                id: saveArrayToFile
                x: 246
                y: 368
                text: qsTr("Save Array")
                anchors.right: quit.left
                anchors.rightMargin: 10
                anchors.verticalCenterOffset: 0
                anchors.verticalCenter: quit.verticalCenter

                onClicked: {

                    selectExisting: false
                    selectFolder: false
                    saveFileDialog.open()
                }


            }

            Text {
                id: note
                text: qsTr("text")
                anchors.bottom: parent.bottom
                color: if(note.text.length <50){ "darkgreen"} else if(note.text.length > 88) { "magenta"} else {"red" }

            }

                Text {
                    id: teksti
                    text: note.text.length
                    anchors.horizontalCenter: parent.horizontalCenter
                }

            Button {
                id: generate
                x: 142
                y: 368
                text: qsTr("Generate")
                anchors.verticalCenter: quit.verticalCenter
                anchors.right: saveArrayToFile.left
                anchors.rightMargin: 10

                onClicked: {
                    arrayFromData.rows = rowsComboBox.currentIndex;
                    arrayFromData.columns = columnsComboBox.currentIndex;
//                    arrayFromData.getArrayDimensions(rowsComboBox.currentIndex,columnsComboBox.currentIndex)
//                    note.text = arrayFromData.checkDimensions(rowsComboBox.currentIndex,columnsComboBox.currentIndex);
                    output.text = arrayFromData.createArray()
                }
            }

            ComboBox {
                id: languageComboBox
                y: 47
                height: 29
                anchors.verticalCenterOffset: 0
                anchors.right: saveEditsToOutput.right
                anchors.rightMargin: -170
                anchors.left: saveEditsToOutput.right
                anchors.leftMargin: 7
                anchors.verticalCenter: inputComboBox.verticalCenter
            }

            Button {
                id: saveEditsToOutput
                y: 97
                text: qsTr("Save Edits")
                anchors.left: edit.right
                anchors.leftMargin: 20
                anchors.verticalCenter: edit.verticalCenter
            }

            Button {
                id: reload
                y: 97
                text: qsTr("Reload")
                anchors.verticalCenterOffset: 0
                anchors.left: load.right
                anchors.leftMargin: 205
                anchors.verticalCenter: load.verticalCenter
            }

            ComboBox {
                id: inputComboBox
                y: 81
                height: 29
                anchors.bottom: load.top
                anchors.bottomMargin: -30
                anchors.right: reload.right
                anchors.rightMargin: 128
                anchors.left: load.left
                anchors.leftMargin: 101
            }

            CheckBox {
                id: replaceCommasWithDots
                text: qsTr("Replace commas with dots")
                anchors.top: inputData.bottom
                anchors.topMargin: 10
                anchors.left: load.left
                anchors.leftMargin: 0
            }

            Label {
                id: arrayLabel
                y: 40
                text: qsTr("Array dimensions")
                anchors.left: edit.left
                anchors.leftMargin: 0
                anchors.bottom: edit.top
                anchors.bottomMargin: 13
            }

            ComboBox {
                id: rowsComboBox
                x: 514
                y: 42
                width: 72
                height: 29
                anchors.right: saveEditsToOutput.right
                anchors.rightMargin: 0
                anchors.verticalCenter: arrayLabel.verticalCenter

                model: 1000

            }

            ComboBox {
                id: columnsComboBox
                y: 42
                width: 69
                height: 29
                anchors.left: languageComboBox.left
                anchors.leftMargin: 0
                anchors.verticalCenter: arrayLabel.verticalCenter

                model: 1000
            }

            Label {
                id: rowsLabel
                y: 16
                text: qsTr("Rows")
                anchors.bottom: rowsComboBox.top
                anchors.bottomMargin: 6
                anchors.left: rowsComboBox.left
                anchors.leftMargin: 0
            }

            Label {
                id: columnsLabel
                y: 16
                text: qsTr("Columns")
                anchors.left: columnsComboBox.left
                anchors.leftMargin: 0
                anchors.verticalCenterOffset: 0
                anchors.verticalCenter: rowsLabel.verticalCenter
            }
        }

}
