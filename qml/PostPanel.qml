import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import MyLib 1.0

import QtGraphicalEffects 1.0

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
                
                
                Image {
                    id: captchaPic

                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.margins: 2
                    opacity: 0.2 //captchaField.focus ? 1 : 0.1

                    //Layout.maximumHeight: sendButton.height
                    fillMode: Image.PreserveAspectFit
                    //Layout.maximumWidth: implicitWidth/2

                    property string captchaID
                    readonly property string url: 'https://2ch.hk/api/captcha/2chaptcha/id?board=' + threadNum.board + '&thread=' + threadNum.thread

                    source: 'https://2ch.hk/api/captcha/2chaptcha/image/' + captchaID

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            var xmlhttp = new XMLHttpRequest()
                            xmlhttp.open('GET', captchaPic.url, false);
                            xmlhttp.send(null);

                            if (xmlhttp.status == 200) {
                                try {
                                    var response = JSON.parse(xmlhttp.responseText)
                                    captchaPic.captchaID = response.id
                                }
                                catch (err) {
                                    console.debug('JSON.parse(' + xmlhttp.responseText + '): ', err)
                                }
                            }
                        }
                    }
                }
            }

            RowLayout {
                TextField {
                    id: captchaValue
                    placeholderText: 'капча'
                    Layout.fillWidth: true
                }

                Button {
                    text: 'post'
                    onClicked: sendPost(threadNum.board, threadNum.thread.toString(), postField.text, captchaPic.captchaID, captchaValue.text)
                }
            }
        }
    }
}
