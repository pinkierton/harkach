import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    id: boardSection
    
    height: 38
    width: ListView.view.width
    color: "#e9883d"
    
    Text {
        anchors.fill: parent
        anchors.leftMargin: 4
        verticalAlignment: Qt.AlignVCenter
        text: section
        renderType: Text.NativeRendering
        color: 'white'
        font.family: 'Noto Sans'
        font.pointSize: 12
    }
    
    Image {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 4
        source: "qrc:/arrow-down-dark.svg"
        width: 24
        height: 24
    }
}
