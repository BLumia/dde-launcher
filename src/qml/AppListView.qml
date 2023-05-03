import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Controls 2.15 as QQC2
import org.deepin.dtk 1.0

Rectangle {
    color: "transparent"

    DelegateModel {
        id: visualModel
        model: sortModel

        delegate: ItemDelegate {
            text: model.display
            checkable: false
            icon.name: "music"
//            icon.source: "image://app-icon/" + iconProviderUrl;
            backgroundVisible: false
        }
    }

    Component {
        id: sectionHeading
        Rectangle {
            height: childrenRect.height
            color: "lightsteelblue"

            required property string section

            QQC2.Label {
                text: parent.section
                font.bold: true
                font.pixelSize: 15
            }
        }
    }

    ListView {
        anchors.fill: parent

        clip: true
        focus: true

        section.property: "category"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading

        model: visualModel

        ScrollBar.vertical: ScrollBar { }
    }
}
