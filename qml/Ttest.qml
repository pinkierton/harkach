import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import MyLib 1.0

import QtQuick.Effects

ItemDelegate {
    id: root

    readonly property string css: "<style type=\"text/css\">\nspan.spoiler, span.spoiler a {background:#BBBBBB;color:green;}\na, .a-link-emulator { color:#FF6600; }\na:hover, .a-link-emulator:hover{color:#0066FF;}\n</style>"
    property string date
    property string src
    property string str
    property int num

    property int posts
    property int files_count
    property int size

    readonly property int __marg: 8
    readonly property int __msgHeight: 210

    property string subj

    property int file_type

    Layout.fillWidth: true
    height: cl.height + __marg*2

    Rectangle {
        id: br
        anchors.fill: parent
        color:'white'
    }

    MultiEffect {
        id: shadow
        source: br
        anchors.fill: br
        shadowBlur: 1.0
        shadowEnabled: true
        shadowColor: "#80000000"
        shadowVerticalOffset: 2
    }

    ColumnLayout {
        id: cl
        anchors.centerIn: parent
        width: parent.width - __marg*2

        RowLayout {
            Text {
                font.pointSize: 14
                text: '#' + num
                renderType: Text.NativeRendering
            }

            Text {
                font.pointSize: 14
                text: subj
                renderType: Text.NativeRendering
                Layout.fillWidth: true
                horizontalAlignment: Qt.AlignHCenter

                textFormat: Text.StyledText

                clip: true

                elide: Text.ElideRight
            }

            Text {
                font.pointSize: 14
                text: date
                renderType: Text.NativeRendering
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: '#c0c1c3'
        }

        RowLayout {
            spacing: 8
            Item {
                width: __msgHeight
                height: __msgHeight
                clip: true

                Image {
                    id: pic
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectCrop
                    source: "https://2ch.hk" + src

                    Text {
                        anchors.centerIn: parent
                    }
                }

                Rectangle {
                    readonly property int r: 2//8

                    anchors.fill: parent
                    anchors.margins: -r
                    color: 'transparent'
                    border.color: "white"
                    border.width: r
                    radius: 2*r
                }
            }

            Item {
                Layout.fillWidth: true
                height: __msgHeight
                clip: true

                Text {
                    anchors.fill: parent
                    text: css + str
                    renderType: Text.NativeRendering
                    linkColor: '#ff6600'
                    wrapMode: Text.WordWrap
                    textFormat: Text.RichText
                    font.pointSize: 11
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: '#c0c1c3'
        }

        RowLayout {
            Item {
                width: 130
            }
            Text {
                font.pointSize: 11
                readonly property string replyPart: posts +  " ОТВЕТОВ"
                readonly property string filesPart: files_count + " С ФАЙЛАМИ"
                readonly property string sizePart:  {
                    var large = size > 1023
                    var suffix = large ? "MB" : "KB"
                    var prefix = large ? (size/1024).toFixed(1) : size
                    return prefix + ' ' + suffix
                }
                text: replyPart + '      ' + filesPart + '      ' + sizePart
                renderType: Text.NativeRendering
            }
        }
    }
}
