import QtQuick 2.15
import QtQml.Models 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.deepin.dtk 1.0

Item {
    width: 780
    height: 600

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        spacing: 10

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                Layout.fillHeight: false

                SearchEdit {
                    id: searchEdit
                    Layout.fillWidth: true
                    placeholder: qsTr("Search")
                    onTextChanged: {
                        console.log(appModel, text)
                        appModel.setFilterRegExp(text)
                    }
                }

                IconButton {
                    icon.name: "switch_to_fullscreen"
                    onClicked: {
                        frame.onToggleFullscreen();
                    }
                }
            }

            AppGridView {
                model: appModel

                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
