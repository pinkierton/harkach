import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import MyLib 1.0

RowLayout {
    id: imgDescription
    spacing: 12
    Image {
        Layout.preferredWidth: 150
        Layout.preferredHeight: 150
        source: "https://2ch.hk" + files[0].thumbnail
        fillMode: Image.PreserveAspectCrop
        clip: true
        
        Rectangle {
            anchors.fill: parent
            anchors.margins: -2
            border.width: 2
            radius: 4
            
            color: files.length > 1 ? '#80000000' : 'transparent'
            border.color: 'white'
            
            Image {
                visible: files.length > 1
                anchors.centerIn: parent
                source: "qrc:/zoom-dark.svg"
                width: 32
                height: 32
            }
        }
    }
    
    ColumnLayout {
        spacing: 0
        Text {
            property string tripPart: '<mark style="color:#228854;">' + trip +'</mark>'
            property string namePart: ((trip !== '') && (name === defaultName)) ? '' : name + ' '

            renderType: Text.NativeRendering
            font.pointSize: 10
            text: index + 1 + ' ' + namePart + tripPart
            color: 'gray'
            textFormat: Text.RichText
        }
        
        Text {
            property string opPart: '<mark style="color:#008000;"> #OP </mark>'
            renderType: Text.NativeRendering
            font.pointSize: 10
            textFormat: Text.RichText
            text: '#' + num + (op ? opPart : ' ') + timestamp.toLocaleString(Qt.locale("ru_RU"), "dd.MM hh:mm:ss")
            color: 'gray'
        }
        
        
        
        Text {
            readonly property string sizePart:  {
                var size = 0
                for (var i=0; i<files.length; i++) {
                    size += files[i].size
                }
                
                var large = size > 1023
                var suffix = large ? "MB" : "KB"
                var prefix = large ? (size/1024).toFixed(1) : size
                return prefix + ' ' + suffix
            }
            
            readonly property string fileString:  {
                var i = files.length
                var fs = (i > 4) ? 'файлов' : ((i > 1) ? 'файла' : 'файл')
                return i + ' ' + fs
            }
            
            readonly property string infoPart: {
                var types = []
                types[1] = 'JPEG'
                types[2] = 'PNG'
                types[4] = 'GIF'
                types[6] = 'WEBM'
                
                var type = files[0].type
                var typePart = types[files[0].type]
                if (typePart === undefined) typePart = 'PNG'
                
                return typePart + ' ' + files[0].imageWidth + 'x' + files[0].imageHeight + ' ' + sizePart
            }
            
            renderType: Text.NativeRendering
            font.pointSize: 10
            text: (files.length > 1) ? sizePart + ' ' + fileString : infoPart
            color: 'gray'
        }
    }
}
