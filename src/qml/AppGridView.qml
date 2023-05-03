import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15
import org.deepin.dtk 1.0

Rectangle {
    color: "transparent"

    property alias placeholderText: placeholderLabel.text
    property alias model: visualModel.model
    readonly property alias count: visualModel.count

    DelegateModel {
        id: visualModel
        delegate: IconItemDelegate {
            iconSource: "image://app-icon/" + iconProviderUrl
        }
    }

    GridView {
        anchors.fill: parent
        cellWidth: 106
        cellHeight: 106

        clip: true
        focus: true

        signal popupMenuRequested(cursorPos: point)

        model: visualModel

        ScrollBar.vertical: ScrollBar { }
    }

    Label {
        id: placeholderLabel
        visible: text !== "" && visualModel.count <= 0
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
