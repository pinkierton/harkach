import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import MyLib 1.0

import QtGraphicalEffects 1.0

PostsView {
    id: postsViewPage

    property string defaultName

    ListView {
        id: view
        anchors.fill: parent
        anchors.margins: 8
        spacing: 10

        model: postModel

        delegate: PostDelegate {
            id: postDelegate
        }
    }

    LoadSplash {
        id: loadSplash
        state: downloading ? "shown" : "hidden"
        anchors.fill: parent

        message: "Загружается список постов"
    }


    focus: true
    Keys.onPressed: {
        switch(event.key) {
            case Qt.Key_PageDown:
                view.flick(0, -3000)
                break;
            case Qt.Key_PageUp:
                view.flick(0, 3000)
                break;
            case Qt.Key_Home:
                view.positionViewAtBeginning()
                break;
            case Qt.Key_End:
                view.positionViewAtEnd()
                break;
            case Qt.Key_Down:
                view.incrementCurrentIndex()
                break
            case Qt.Key_Up:
                view.decrementCurrentIndex()
                break
            default:
                break
        }
    }
}
