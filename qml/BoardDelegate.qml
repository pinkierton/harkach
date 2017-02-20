import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    id: boardElementDelegate
    height: 38
    width: ListView.view.width
    
    color: '#fcfcfc'
    
    property alias text: boardLabel.text
    readonly property string board_id: model.board_id
    readonly property string default_name: model.default_name
    
    Text {
        id: boardLabel
        anchors.fill: parent
        anchors.leftMargin: 4
        
        horizontalAlignment: Qt.AlignLeft
        verticalAlignment: Qt.AlignVCenter
        text: '/' + board_id + '/ ‒ ' + name
        renderType: Text.NativeRendering
        
        font.pointSize: 10
        font.family: 'Noto Sans'
    }
    
    MouseArea {
        id: boardElementMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: boardElementDelegate.ListView.view.currentIndex = index
    }
    
    Image {
        id: boardElementIcon
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 4
        source: "qrc:/arrow-right.svg"
        width: 24
        height: 24
    }
    
    states: [
        State {
            name: 'active'
            when: boardElementDelegate.ListView.isCurrentItem
            PropertyChanges {
                target: boardElementDelegate
                color: '#3daee9'
            }
            PropertyChanges {
                target: boardLabel
                color: 'white'
            }
            PropertyChanges {
                target: boardElementIcon
                source: "qrc:/arrow-right-dark.svg"
            }
        },
        State {
            name: "hovered"
            when: boardElementMouseArea.containsMouse
            PropertyChanges {
                target: boardElementDelegate
                color: '#d6edf9'
            }
        }
    ]
    
    transitions: [
        Transition {
            ColorAnimation { duration: 100 }
        },
        Transition {
            to: "active"
            ColorAnimation { duration: 250 }
        }
    ]
}
