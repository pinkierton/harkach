import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import MyLib 1.0

import QtGraphicalEffects 1.0

ApplicationWindow {
    id: appWin
    width: 1366
    height: 768
    visible: true
    title: "Два.ч — Майорное общение"

    readonly property BoardDelegate currentBoard: boardsView.currentItem
    readonly property string board_id: (currentBoard !== null) ? currentBoard.board_id : ''
    readonly property string default_name: (currentBoard !== null) ? currentBoard.default_name : ''

    property var threadNum: makeThreadNum('', 0, '')
    //property alias threadNum: postsViewPage.threadNum

    header: TopToolBar { id: topToolBar }

    Drawer {
        id: boardsPanel
        background: Rectangle { color: '#c0c1c3' }
        clip: true
        width: 340
        height: parent.height



        BoardsView {
            id: boardsView
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        onCurrentItemChanged: {
            currentItem.forceActiveFocus()
            if (currentItem == threadsViewPage) {
                swipeView.removeItem(1)
                threadNum = makeThreadNum('', 0, '')
            }
        }

        ThreadsViewPage {
            id: threadsViewPage
            board: board_id
            onClicked: {
                threadNum = makeThreadNum(board, post, subj)
                swipeView.addItem(postsViewLoader.item)
                swipeView.setCurrentIndex(1)
                swipeView.currentItem.forceActiveFocus()
            }
        }

//        Loader {
//            active: threadNum.board
//            //id: loader_postsViewPage
//            sourceComponent: PostsViewPage {
//                id: postsViewPage
//                threadNum: appWin.threadNum
//                //defaultName: appWin.de
//            }
//        }

    }

    PostPanel {
        id: postPanel
        onClosed: swipeView.currentItem.forceActiveFocus()
    }


    property var postsViewLoader: Loader {
        active: threadNum.board
        sourceComponent: PostsViewPage {
            id: postsViewPage
            threadNum: appWin.threadNum
        }
    }
}
