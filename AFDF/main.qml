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
    width: Screen.width/2
    height: Screen.height/2
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
                inputData.text = arrayFromData.getTheData();

            }
            onRejected: {
                console.log("Canceled")

            }

        }




    Item {
        id: mainItem
        anchors.fill: parent

        Button {
            id: load
            y: 97
            text: qsTr("Load File")
            anchors.left: inputData.left
            anchors.leftMargin: 0
            anchors.bottom: inputData.top
            anchors.bottomMargin: 10

            onClicked: {
                fileDialog.open()

            }
        }

        Button {
            id: edit
            y: 97
            text: qsTr("Edit")
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

        Button {
            id: generate
            x: 142
            y: 368
            text: qsTr("Generate")
            anchors.verticalCenter: quit.verticalCenter
            anchors.right: saveArrayToFile.left
            anchors.rightMargin: 10

            onClicked: {
                output.text = arrayFromData.getOutputData()
            }
        }

        ComboBox {
            id: languageComboBox
            y: 47
            height: 29
            anchors.right: saveEditsToOutput.right
            anchors.rightMargin: 0
            anchors.left: edit.left
            anchors.leftMargin: 0
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
            anchors.left: load.right
            anchors.leftMargin: 20
            anchors.verticalCenter: load.verticalCenter
        }

        ComboBox {
            id: inputComboBox
            y: 47
            height: 29
            anchors.bottom: load.top
            anchors.bottomMargin: 20
            anchors.right: reload.right
            anchors.rightMargin: 0
            anchors.left: load.left
            anchors.leftMargin: 0
        }

        CheckBox {
            id: replaceCommasWithDots
            y: 37
            text: qsTr("Replace commas with dots")
            anchors.bottom: inputComboBox.top
            anchors.bottomMargin: 15
            anchors.left: load.left
            anchors.leftMargin: 0
        }
    }





}
