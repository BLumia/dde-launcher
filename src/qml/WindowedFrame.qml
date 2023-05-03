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
            Layout.fillWidth: false
            Layout.preferredWidth: 300
            Layout.fillHeight: true

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: false

                Label {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: qsTr("Categories")
                }

                ButtonBox {
                    ToolButton { icon.name: "search" }
                    ToolButton { icon.name: "search"; checked: true }
                }
            }

            AppListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 50

                Rectangle {
                    color: 'teal'
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Text {
                        anchors.centerIn: parent
                        text: parent.width + 'x' + parent.height
                    }
                }

                Rectangle {
                    color: 'teal'
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Text {
                        anchors.centerIn: parent
                        text: parent.width + 'x' + parent.height
                    }
                }
            }
        }

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

            Label {
                visible: favoriteGridView.visible
                text: qsTr("My Favorites")
            }

            AppGridView {
                id: favoriteGridView
                model: favoriteModel
                visible: searchEdit.text === ""
                placeholderText: qsTr("Add your favorite apps here")

                property int rowCount: Math.min(Math.ceil(count / 4), 2)

                Layout.preferredHeight: rowCount == 0 ? 50 : rowCount * 100
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("All Apps")
            }

            AppGridView {
                model: appModel

                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
