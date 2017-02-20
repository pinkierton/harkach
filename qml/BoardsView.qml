import QtQuick 2.7
import QtQuick.Controls 2.0

ListView {
    id: boardView
    anchors.fill: parent
    model: boardModel
    currentIndex: -1
    boundsBehavior: Flickable.StopAtBounds    
    section.property: "category"
    section.criteria: ViewSection.FullString
    section.delegate: BoardSection {}
    delegate: BoardDelegate {}
    ScrollIndicator.vertical: ScrollIndicator { width: 8 }
}
