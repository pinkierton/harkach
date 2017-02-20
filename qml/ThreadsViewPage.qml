import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import MyLib 1.0

ThreadsView {
    id: threadsViewPage

    signal clicked(string board, string subj, int post)

    Image {
        anchors.fill: parent
        source: "qrc:/back.gif"
        fillMode: Image.Tile
    }

    ListView {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 10

        cacheBuffer: Math.max(height * 3, 320) //contentHeight > 0 ? contentHeight : 320

        model: threadModel

        delegate: Ttest {
            Layout.fillWidth: false
            width: ListView.view.width

            date: time_stamp.toLocaleString(Qt.locale("ru_RU"), "dd/mm/yy ddd hh:MM:ss")
            src: files[0].thumbnail
            str: comment
            subj: subject
            num: post_num

            posts: posts_count
            files_count: 0
            size: 0//151
            file_type: files[0].type

            onClicked: threadsViewPage.clicked(board, subject, post_num)
        }

        ScrollIndicator.vertical: ScrollIndicator {}
    }

    LoadSplash {
        id: loadSplash
        state: downloading ? "shown" : "hidden"
        anchors.fill: parent
    }
}
