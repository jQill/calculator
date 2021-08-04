import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import Calc 1.0

ApplicationWindow {
    id:root
    width: 640
    maximumHeight: 60
    minimumHeight: 60
    visible: true

    property int fb_width: 40
    property int ib_width: 60
    property int b_height: 20

    CalcModel{
        id:calc
    }

    Row{
        id:textField

        TextField{
            text: calc.exp
            placeholderText: qsTr("Enter your expression")
            onEditingFinished: calc.setExp(text)
            width: root.width*4/5
        }
        TextField{
            width: root.width/5
            text: calc.error==-1? calc.res : qsTr("")
        }
    }
    Row{
        id:row

        anchors.top:textField.bottom
        spacing: 3

        Button{
            id:int_button
            highlighted: true
            height: b_height
            width: ib_width
            text: qsTr("rational")
            onClicked: {
                calc.setType(false)
                float_button.highlighted = false
                int_button.highlighted = true
            }
        }
        Text{
            text:"/"
            anchors.verticalCenter: row.verticalCenter
        }
        Button{
            id:float_button
            height: b_height
            width: fb_width
            text: qsTr("real")
            onClicked: {
                calc.setType(true)
                float_button.highlighted = true
                int_button.highlighted = false
            }
        }
        Text{
            text:"field"
            anchors.verticalCenter: row.verticalCenter
        }
    }
    Rectangle{
        anchors.right: textField.right
        anchors.top: textField.bottom
        anchors.rightMargin: root.width/12
        visible: calc.error == -1 ? false : true
        radius: 10
        height: b_height
        width: root.width*2/5
        border.color: "gray"
        Text {
            anchors.right: parent.right
            anchors.rightMargin: parent.width/15
            anchors.verticalCenter: parent.verticalCenter
            text: calc.res
        }
    }
}
