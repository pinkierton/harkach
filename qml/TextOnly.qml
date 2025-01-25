import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import MyLib 1.0

ColumnLayout {
    RowLayout {
        Text {
            readonly property string tripPart: '<mark style="color:#228854;">' + trip +'</mark>'
            readonly property string namePart: name + ' '
            readonly property string nameWithTrip: namePart+tripPart
            readonly property string opPart: '<mark style="color:#008000;"> #OP </mark>'
            readonly property string numWithTime: '#' + num + (op ? opPart : ' ') + timestamp.toLocaleString(Qt.locale("ru_RU"), "dd.MM hh:mm:ss")

            renderType: Text.NativeRendering
            font.pointSize: 10
            text: index + 1 + ' ' + nameWithTrip + ((trip !== '' )  ? '<br>' : '') + numWithTime
            color: 'gray'
            textFormat: Text.RichText
        }
    }
}
