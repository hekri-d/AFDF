import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
id: ajtemi
    Text {
        id: name
        text: qsTr("text")
        width: parent.width/2
        height: parent.height/10
        anchors.left: parent.left
       }


    CheckBox {
        id: checku
        anchors.left: name.right
        anchors.leftMargin: 20
        anchors.top: name.top
        width: 50;
        height: name.height
    }

}
