import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import MyLib 1.0

import QtGraphicalEffects 1.0

ToolBar {
    id: topToolBar

    property alias header: headerText.text

    background: Item {
        Rectangle {
            id: aa
            anchors.fill: parent
            color:  '#eeeeee' // '#ff6600'// //'#e9883d'
        }
        
        DropShadow {
            id: shadow
            anchors.fill: parent
            horizontalOffset: 2
            verticalOffset: 2
            radius: 10.0
            samples: 17
            color: "#80000000"
            source: aa
        }
    }
    
    RowLayout {
        anchors.fill: parent
        spacing: 0
        
        Item {
            Layout.minimumWidth: boardsView.width * boardsView.position
            //height: 40
        }
        
        ToolButton {
            enabled: !boardsPanel.position
            onClicked: swipeView.currentIndex ? swipeView.setCurrentIndex(0) : boardsPanel.open()
            contentItem: Item {
                Image {
                    anchors.centerIn: parent
                    width: 32
                    height: 32
                    source: "qrc:/draw-arrow-back.svg"
                }
            }
        }
        
        Text {
            id: headerText
            text: threadNum.thread && swipeView.currentIndex === 1
                  ? threadNum.subj
                  : Boolean(currentBoard) ? currentBoard.text : 'Разделы'
            font.pointSize: 14
            renderType: Text.NativeRendering

            textFormat: Text.RichText
            font.weight: Font.Thin
        }
        
        Item { Layout.fillWidth: true }
        
        Loader {
            active: threadNum.thread
            sourceComponent: ToolButton {
                contentItem: Item {
                    Image {
                        anchors.centerIn: parent
                        width: 32
                        height: 32
                        source: "qrc:/document-edit.svg"
                    }
                }
                onClicked: postPanel.open()
            }
        }

        
        ToolButton {
            contentItem: Item {
                Image {
                    anchors.centerIn: parent
                    width: 32
                    height: 32
                    source: "qrc:/view-refresh.svg"
                }
            }
            onClicked: {
                if (swipeView.currentIndex) {
                    swipeView.currentItem.updatePage()
                    swipeView.currentItem.forceActiveFocus()
                }
            }
        }
        
        ToolButton {
            contentItem: Item {
                Image {
                    anchors.centerIn: parent
                    width: 32
                    height: 32
                    source: "qrc:/application-menu.svg"
                }
            }
        }
    }
}
