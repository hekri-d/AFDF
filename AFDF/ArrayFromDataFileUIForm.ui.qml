import QtQuick 2.4
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4

Item {
    id: mainItem
    width: 766
    height: 600

    property alias quitProperty: quit

    Button {
        id: load
        y: 97
        text: qsTr("Load")
        anchors.left: inputData.left
        anchors.leftMargin: 0
        anchors.bottom: inputData.top
        anchors.bottomMargin: 10
    }

    Button {
        id: edit
        y: 97
        text: qsTr("Edit")
        anchors.verticalCenter: load.verticalCenter
        anchors.left: output.left
        anchors.leftMargin: 0
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
    }

    Button {
        id: button3
        x: 246
        y: 368
        text: qsTr("Button")
        anchors.right: quit.left
        anchors.rightMargin: 10
        anchors.verticalCenterOffset: 0
        anchors.verticalCenter: quit.verticalCenter
    }

    Button {
        id: generate
        x: 142
        y: 368
        text: qsTr("Generate")
        anchors.verticalCenter: quit.verticalCenter
        anchors.right: button3.left
        anchors.rightMargin: 10
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
        text: qsTr("Save")
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
        id: replaceCommasWithDot
        y: 37
        text: qsTr("Replace commas with dots")
        anchors.bottom: inputComboBox.top
        anchors.bottomMargin: 15
        anchors.left: load.left
        anchors.leftMargin: 0
    }
}
