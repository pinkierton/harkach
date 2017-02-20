import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import MyLib 1.0

Rectangle {
    id: loadSplash
    color: 'black'
    property alias message: splashText.text
    
    states: [
        State {
            name: "shown"
            PropertyChanges { target: loadSplash; opacity: 0.7 }
        },
        State {
            name: "hidden"
            PropertyChanges { target: loadSplash; opacity: 0.0 }
        }
    ]
    
    transitions: Transition {
        OpacityAnimator {
            target: loadSplash
            duration: 300
        }
    }
    
    BusyIndicator {
        id: control
        
        Text {
            id: splashText
            anchors.bottom: parent.top
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            
            color: 'white'
            font.pointSize: 16
            
            text: "Загружается список тредов"
        }
        
        anchors.centerIn: parent
        running: true
        
        contentItem: Item {
            implicitWidth: 64
            implicitHeight: 64
            
            Item {
                id: item
                x: parent.width / 2 - 32
                y: parent.height / 2 - 32
                width: 64
                height: 64
                opacity: control.running ? 1 : 0
                
                Behavior on opacity {
                    OpacityAnimator {
                        duration: 250
                    }
                }
                
                RotationAnimator {
                    target: item
                    running: control.visible && control.running
                    from: 0
                    to: 360
                    loops: Animation.Infinite
                    duration: 1250
                }
                
                Repeater {
                    id: repeater
                    model: 6
                    
                    Rectangle {
                        x: item.width / 2 - width / 2
                        y: item.height / 2 - height / 2
                        implicitWidth: 10
                        implicitHeight: 10
                        radius: 5
                        color: "orange"
                        transform: [
                            Translate {
                                y: -Math.min(item.width, item.height) * 0.5 + 5
                            },
                            Rotation {
                                angle: index / repeater.count * 360
                                origin.x: 5
                                origin.y: 5
                            }
                        ]
                    }
                }
            }
        }
    }
}
