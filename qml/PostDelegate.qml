import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import MyLib 1.0

import QtGraphicalEffects 1.0

Item {
    id: postDelegate

    readonly property string css: "<style type=\"text/css\">\nspan.spoiler, span.spoiler a {background:#BBBBBB;color:green;}\na, .a-link-emulator { color:#FF6600; }\na:hover, .a-link-emulator:hover{color:#0066FF;}\n</style>"
    
    width: ListView.view.width
    height: cl.height
    
    ColumnLayout {
        id: cl
        anchors.left: parent.left
        anchors.right: parent.right

        Loader {
            active: files.length > 0
            sourceComponent: ImgDescription{}
        }

        Loader {
            active: files.length === 0
            sourceComponent: TextOnly {}
        }
        
        Text {
            Layout.fillWidth: true
            text: css + comment
            renderType: Text.NativeRendering
            linkColor: '#ff6600'
            wrapMode: Text.WordWrap
            textFormat: Text.RichText
            font.pointSize: 10
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: '#c0c1c3'
        }
    }
}
