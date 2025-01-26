import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import MyLib 1.0

Drawer {
    id: postPanel
    edge: Qt.RightEdge
    width: 500
    height: parent.height
    
    background: Rectangle { color: '#c0c1c3' }
    clip: true
    
    Rectangle {
        anchors.fill: parent
        color: '#eeeeee'
    }
    
    Item {
        anchors.fill: parent
        
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 8
            spacing: 8
            
            TextField {
                id: threadField
                placeholderText: 'e-mail'
                Layout.fillWidth: true
            }
            
            TextField {
                placeholderText: 'имя'
                Layout.fillWidth: true
            }
            
            TextField {
                placeholderText: 'тема'
                Layout.fillWidth: true
            }
            
            TextArea {
                id: postField
                placeholderText: 'комментарий'
                
                background: Rectangle {
                    //implicitWidth: 200
                    implicitHeight: 40
                    border.color: parent.enabled ? (parent.focus ? '#0066ff' : '#bdbebf') : "transparent"
                    border.width: parent.focus ? 2 : 1
                }
                
                Layout.fillWidth: true
                Layout.fillHeight: true
                
                wrapMode: TextEdit.WordWrap
            }

            RowLayout {
                TextField {
                    id: captchaValue
                    placeholderText: 'капча'
                    Layout.fillWidth: true
                }

                Button {
                    text: 'post'
                    onClicked: sendPost(threadNum.board, threadNum.thread.toString(), postField.text, "", captchaValue.text)
                }
            }
        }
    }
}
