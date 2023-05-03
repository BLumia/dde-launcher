import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import org.deepin.dtk 1.0

Item {
    width: 96
    height: 96

    property alias iconSource: iconImage.source

    Rectangle {
        anchors.fill: parent
        color: stylus.hovered ? "black" : "transparent"

        Behavior on color { PropertyAnimation {} }

        Column {
            anchors.fill: parent

            Image {
                id: iconImage
                anchors.horizontalCenter: parent.horizontalCenter
                source: iconSource
                sourceSize: Qt.size(48, 48)
            }

            Label {
                text: display
                textFormat: Text.PlainText
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                elide: Text.ElideRight
                maximumLineCount: 2
            }
        }
    }

    TapHandler {
        acceptedButtons: Qt.RightButton
        onTapped: {
            menuWorker.showMenuByAppItem(mapToGlobal(point.position), visualModel.modelIndex(index))
        }
    }

    HoverHandler {
        id: stylus
    }
}
